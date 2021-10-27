#!/usr/bin/env python3
import autograde
import os, os.path

assignment_name = 'PA1'
release='1'

autograde.Test.time_limit = 60

class StanzaTests(autograde.StringTests):
    def get_tests(self, project, prog, build_dir, data_dir):
        test_file = os.path.join(data_dir, self.file)
        test_group = project + ':' + self.name if self.name else project
        prog = './' + prog

        if not os.path.exists(test_file):
            autograde.logger.warning('Test file not found: %r', self.file)
            return

        autograde.logger.debug('Opening test file: %r', self.file)

        with open(test_file) as lines:
            args = [prog]
            for line in lines:
                line = line.strip()
                if line.startswith('@'):
                    args.append(line[1:])
                else:
                    yield self.Test(cmd      = args,
                                    ref      = line,
                                    category = self.category,
                                    group    = test_group,
                                    weight   = self.weight,
                                    dir      = build_dir)
                    args = [prog]

class ErrorStringTests(autograde.StringTests):
    @staticmethod
    def Test(**kws):
        return autograde.RefTest(ref_code = 1, **kws)

assignment = autograde.MultiProject(
    StanzaTests.Project('whisper'),
    autograde.StringTests.Project('anagram'),
    autograde.Project('balance',
        autograde.StringTests(id = '1', name = '', weight = 0.5),
        ErrorStringTests(id = '2', name = '', weight = 0.5)
    ),
    autograde.StdinFileTests.Project('list', weight=2),
    autograde.FileTests.Project('mexp', weight=2),
    autograde.Project('bst',
        autograde.StdinFileTests(id='1', weight=1.5),
        autograde.StdinFileTests(id='2', weight=1.5),
    )
)


if __name__ == '__main__':
    autograde.main(assignment_name, assignment, release)
