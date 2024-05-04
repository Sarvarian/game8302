""" Helper function for code c++ generator """

import os
import os.path


class Conversion:
    """ Conversion Routine """

    def __init__(self, main_type: str, other_type: str):
        self.type: str = main_type
        self.other: str = other_type
        self.head: str = ''
        self.body: str = ''

    def generate_head(self) -> None:
        """ Generate head of conversion routine. """
        self.head = '\t' + self.other + \
            ' to_' + self.other + '() const;'

    def generate_body(self) -> None:
        """ Generate body of conversion routine. """
        self.body = 'inline ' + self.other + ' ' + self.type + \
            '::to_' + self.other + '() const\n'
        self.body += '{\n'
        self.body += '\treturn ' + \
            self.other + '((' + self.other + '::Raw)(value_));\n'
        self.body += '}\n\n'

    def generate(self) -> None:
        """ Generate head and body of conversion routine. """
        self.generate_head()
        self.generate_body()


class Type:
    """ Just Type """

    def __init__(self, raw_type_name: str, type_name: str, default_value: str) -> None:
        self.raw: str = raw_type_name
        self.name: str = type_name
        self.default: str = default_value

    def public_method(self) -> None:
        """ public method """

    def public_method2(self) -> None:
        """ public method """


def read_content(file_path: str) -> str:
    """Returns content of a text file.
    file_path: Give a full path. (relative or absolute does not matter.)
    """
    with open(file_path, 'rt', encoding='utf-8') as file:
        content = file.read().strip()
        file.close()
        return content


def write_content(file_path: str, content: str) -> None:
    """Write content to a text file.
    file_path: Give a full path. (relative or absolute does not matter.)
    content: String of text.
    """
    with open(file_path, 'w', encoding='utf-8', newline='\n') as file:
        file.write(content)
        file.close()


def read_types(file_path: str) -> list[Type]:
    """Returns a list of dictionaries of types.
    file_path: Give full path to types list file. (relative or absolute does not matter.)
    """
    types = read_content(file_path).split()
    res: list[Type] = []
    i = 0
    while i < len(types):
        res.append(Type(types[i], types[i+1], types[i+2]))
        i += 3
    return res


def read_routine_templates(dir_path: str) -> dict[str, str]:
    """Returns a dictionary of types and their routines.
    dir_path: Give full path to routine template directory. (relative or absolute does not matter.)
    """
    names = os.listdir(dir_path)
    res: dict[str, str] = {}
    for name in names:
        path = os.path.join(dir_path, name)
        if os.path.isdir(path):
            continue
        name = name.removesuffix('.hpp')
        res[name] = read_content(path)
        res[name] = res[name].replace('\n', '\n\t')
        res[name] = res[name].replace('\n\t\n', '\n\n')
    return res
