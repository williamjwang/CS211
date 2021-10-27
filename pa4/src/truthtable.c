#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// enum gate_type{NOT, AND, OR, NAND, NOR, XOR, DECODER, MULTIPLEXER, PASS};

typedef struct gate
{
    //enum gate_type
    char type[13];
    int *inputs;
    int *outputs;
    int *selectors;
    int numInputs;
    int numOutputs;
} gate;

void Not(int *values, int inputIndex, int outputIndex)
{
    values[outputIndex] = !values[inputIndex];
}
void And(int *values, int inputIndex1, int inputIndex2, int outputIndex)
{
    values[outputIndex] = values[inputIndex1] && values[inputIndex2];
}
void Or(int *values, int inputIndex1, int inputIndex2, int outputIndex)
{
    values[outputIndex] = values[inputIndex1] || values[inputIndex2];
}
void Nand(int *values, int inputIndex1, int inputIndex2, int outputIndex)
{
    values[outputIndex] = !(values[inputIndex1] && values[inputIndex2]);
}
void Nor(int *values, int inputIndex1, int inputIndex2, int outputIndex)
{
    values[outputIndex] = !(values[inputIndex1] || values[inputIndex2]);
}
void Xor(int *values, int inputIndex1, int inputIndex2, int outputIndex)
{
    values[outputIndex] = values[inputIndex1] ^ values[inputIndex2];
}
void Decoder(int* values, int numInputs, int* inputs, int* outputs)
{
    int x = 0;
    for (int i = 0; i < (1 << numInputs); i++) values[outputs[i]] = 0;
    for (int i = 0; i < numInputs; i++) x += values[inputs[i]] << (numInputs - i - 1);
    values[outputs[x]] = 1;
}
void Multiplexer(int *values, int numSelectors, int* inputs, int* selectors, int outputIndex)
{
    int x = 0;
    for (int i = 0; i < numSelectors; i++) x += values[selectors[i]] << (numSelectors - i - 1);
    values[outputIndex] = values[inputs[x]];
}
void Pass(int *values, int inputIndex, int outputIndex)
{
    values[outputIndex] = values[inputIndex];
}

int findIndex(int size, char **vars, char *var)
{
    for (int i = 0; i < size; i++)
    {
        if (strcmp(vars[i], var) == 0) return i;
    }
    return -1;
}

int increment(int *arr, int icount)
{
    for (int i = icount + 1; i >= 2; i--)
    {
        arr[i] = !arr[i];
        if (arr[i] == 1) return 1;
    }
    return 0;
}

int main(int argc, char** argv)
{
    if (argc != 2) return EXIT_FAILURE;
    FILE *file = fopen(argv[1], "r");
    if (file == NULL) return EXIT_FAILURE;

    int numInputs = 0;
    int numOutputs = 0;
    int size = 2;
    char* str = malloc(17 * sizeof(char));

    fscanf(file, " %16s", str);
    fscanf(file, " %d", &numInputs);

    size += numInputs;
    char** vars = malloc(size * sizeof(char *));

    for(int i = 0; i < size; i++) vars[i] = (char*)malloc(17*sizeof(char));  
    strcpy(vars[0], "0\0");
    strcpy(vars[1], "1\0");
    for (int i = 0; i < numInputs; i++)
    {
        fscanf(file, " %16s", str);
        strcpy(vars[i + 2], str);
    }

    fscanf(file, " %16s", str);
    fscanf(file, "%d", &numOutputs);
    size += numOutputs;
    vars = realloc(vars, size * sizeof(char*));

    for (int i = 0; i < numOutputs; i++) vars[i + 2 + numInputs] = (char*)malloc(17 * sizeof(char));  
    for (int i = 0; i < numOutputs; i++)
    {
        fscanf(file, " %16s", str);
        strcpy(vars[2 + numInputs + i], str);
    }

    gate* gateList = NULL;
    int gateCount = 0;
    int tempCount = 0;

    while (feof(file) != 1)
    {
        gate g;
        g.numInputs = 0;
        g.numOutputs = 0;
        gateCount++;

        fscanf(file, " %s", str);
        strcpy(g.type, str);
        // if (strcmp(str, "NOT") == 0) g.type = NOT;
        // if (strcmp(str, "AND") == 0) g.type = AND;
        // if (strcmp(str, "OR") == 0) g.type = OR;
        // if (strcmp(str, "NAND") == 0) g.type = NAND;
        // if (strcmp(str, "NOR") == 0) g.type = NOR;
        // if (strcmp(str, "XOR") == 0) g.type = XOR;
        // if (strcmp(str, "DECODER") == 0) g.type = DECODER;
        // if (strcmp(str, "MULTIPLEXER") == 0) g.type = MULTIPLEXER;
        // if (strcmp(str, "PASS") == 0) g.type = PASS;

        int inC = 2;
        int numOutputs = 1;

        if ((strcmp(str, "NOT") == 0) || (strcmp(str, "PASS") == 0)) inC = 1;
        else if (strcmp(str, "DECODER") == 0)
        {
            fscanf(file, "%d", &inC);
            g.numInputs = inC;
            numOutputs = (1 << inC);
        }
        else if (strcmp(str, "MULTIPLEXER") == 0)
        {
            fscanf(file, "%d", &inC);
            g.numOutputs = inC;
            inC = (1 << inC);
        }

        g.inputs = malloc(inC * sizeof(int));
        g.outputs = malloc(numOutputs * sizeof(int));
        g.selectors = malloc(g.numOutputs * sizeof(int));

        for (int i = 0; i < inC; i++)
        {
            fscanf(file, " %16s", str);
            g.inputs[i] = findIndex(size, vars, str);
        }
        for (int i = 0; i < g.numOutputs; i++)
        {
            fscanf(file, " %16s", str);
            g.selectors[i] = findIndex(size, vars, str);
        } 
        for (int i = 0; i < numOutputs; i++)
        {
            fscanf(file, " %16s", str);
            int index = findIndex(size, vars, str);
            if (index != -1) g.outputs[i] = index;
            else if (index == -1)
            {
                size++;
                tempCount++;
                vars = realloc(vars, size * sizeof(char *));
                vars[size - 1] = malloc(17 * sizeof(char));
                strcpy(vars[size - 1], str);
                g.outputs[i] = size - 1;
            }
        }
        
        if (!gateList) gateList = malloc(sizeof(gate));
        else gateList = realloc(gateList, gateCount * sizeof(gate));        
        gateList[gateCount - 1] = g;
    }

    int* values = malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) values[i] = 0;
    values[1] = 1;

    while(1)
    {
        for (int i = 0; i < numInputs; i++) printf("%d ", values[i + 2]);        
        printf("|");

        for (int i = 0; i < gateCount; i++)
        {
            gate g = gateList[i];
            // if (g.type == NOT) Not(values, g.inputs[0], g.outputs[0]);            
            // if (g.type == AND) And(values, g.inputs[0], g.inputs[1], g.outputs[0]);
            // if (g.type == OR) Or(values, g.inputs[0], g.inputs[1], g.outputs[0]);
            // if (g.type == NAND) Nand(values, g.inputs[0], g.inputs[1], g.outputs[0]);            
            // if (g.type == NOR) Nor(values, g.inputs[0], g.inputs[1], g.outputs[0]);            
            // if (g.type == XOR) Xor(values, g.inputs[0], g.inputs[1], g.outputs[0]);
            // if (g.type == DECODER) Decoder(values, g.numInputs, g.inputs, g.outputs);
            // if (g.type == MULTIPLEXER) Multiplexer(values, g.numOutputs, g.inputs, g.selectors, g.outputs[0]);
            // if (g.type == PASS) Pass(values, g.inputs[0], g.outputs[0]);
            if (strcmp(g.type, "NOT") == 0) Not(values, g.inputs[0], g.outputs[0]);            
            if (strcmp(g.type, "AND") == 0) And(values, g.inputs[0], g.inputs[1], g.outputs[0]);
            if (strcmp(g.type, "OR") == 0) Or(values, g.inputs[0], g.inputs[1], g.outputs[0]);
            if (strcmp(g.type, "NAND") == 0) Nand(values, g.inputs[0], g.inputs[1], g.outputs[0]);            
            if (strcmp(g.type, "NOR") == 0) Nor(values, g.inputs[0], g.inputs[1], g.outputs[0]);            
            if (strcmp(g.type, "XOR") == 0) Xor(values, g.inputs[0], g.inputs[1], g.outputs[0]);
            if (strcmp(g.type, "DECODER") == 0) Decoder(values, g.numInputs, g.inputs, g.outputs);
            if (strcmp(g.type, "MULTIPLEXER") == 0) Multiplexer(values, g.numOutputs, g.inputs, g.selectors, g.outputs[0]);
            if (strcmp(g.type, "PASS") == 0) Pass(values, g.inputs[0], g.outputs[0]);
        }

        for (int i = 0; i < numOutputs; i++) printf(" %d", values[numInputs + i + 2]);        
        printf("\n");
        if (!increment(values, numInputs)) break;        
    }

    //Free dynamically allocated memory
    for (int i = 0; i < gateCount; i++)
    {
        free(gateList[i].inputs);
        free(gateList[i].outputs);
        free(gateList[i].selectors);
    }
    free(gateList);
    for (int i = 0; i < size; i++)
    {
        free(vars[i]);
    }
    free(vars);
    free(values);
    free(str);
    fclose(file);
    return EXIT_SUCCESS;
}