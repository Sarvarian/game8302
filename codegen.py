"""" To generate c++ code. """

import os
import os.path


TEMPLATES_DIR = 'ab/__templates'
OUTPUT_DIR = 'ab/'
OUTPUT_FILE_NAME = 'code_gen_output.hpp'
OUTPUT_FILE_PATH = os.path.join(OUTPUT_DIR, OUTPUT_FILE_NAME)

BODY_TEMPLATE_FILE_NAME = 'math.hpp'  # set_main_template_file_name
BODY_TEMPLATE_FILE_PATH = os.path.join(TEMPLATES_DIR, BODY_TEMPLATE_FILE_NAME)

GENERATE_TYPES_HERE_PLACEHOLDER_STRING = '//_GENERATE_TYPE_HERE'
PREDEFINE_TYPES_HERE_PLACEHOLDER_STRING = '//_PREDEFINE_TYPE_HERE'

TYPES_LIST_FILE_NAME = 'types.txt'
TYPES_LIST_FILE_PATH = os.path.join(TEMPLATES_DIR, TYPES_LIST_FILE_NAME)

STRUCT_FILE_NAME = 'struct.hpp'
STRUCT_FILE_PATH = os.path.join(TEMPLATES_DIR, STRUCT_FILE_NAME)

ROUTINES_PLACEHOLDER_STRING = '//_GENERATE_ROUTINES_HERE'
TYPE_NAME_PLACEHOLDER_STRING = '_TYPE_NAME'
RAW_TYPE_NAME_PLACEHOLDER_STRING = '_RAW_TYPE'
DEFAULT_VALUE_PLACEHOLDER_STRING = '_DEFAULT_VALUE'

ROUTINES_TEMPLATES_DIR_NAME = 'routines'
ROUTINES_TEMPLATES_DIR_PTAH = os.path.join(
    TEMPLATES_DIR, ROUTINES_TEMPLATES_DIR_NAME)

EVERY_TYPE_ROUTINES_FILE_NAME_WITHOUT_EXTENSION = '_every'

CONVERSIONS_DIR_NAME = 'conversions'
CONVERSIONS_DIR_PATH = os.path.join(TEMPLATES_DIR, CONVERSIONS_DIR_NAME)

EVERY_TYPE_CONVERSION_TEMPLATE_FILE_NAME = '_every'


templates_dir: str = ''
output_dir: str = ''
output_file: str = ''
main_template_file: str = ''
types_list_file: str = ''
struct_template_file: str = ''
routines_templates_dir: str = ''
every_type_routines_file_name_without_extension: str = ''
conversions_dir: str = ''
every_type_conversion_template_file_name: str = ''


class FileSystem:
    """ To Work With Files And Directories """

    def __init__(self) -> None:
        self.templates_dir: str = templates_dir
        self.output_dir: str = output_dir
        self.output_file: str = os.path.join(output_dir, output_file)
        self.main_template_file: str = os.path.join(
            templates_dir, main_template_file)
        self.types_list_file: str = os.path.join(
            templates_dir, types_list_file)
        self.struct_template_file: str = os.path.join(
            templates_dir, struct_template_file)
        self.routines_templates_dir: str = os.path.join(
            templates_dir, routines_templates_dir)
        self.every_type_routines_file_name_without_extension: str = \
            every_type_routines_file_name_without_extension
        self.conversions_dir_name: str = os.path.join(
            templates_dir, conversions_dir)
        self.every_type_conversion_template_file_name: str = \
            every_type_routines_file_name_without_extension


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


class Conversion:
    """ Conversion Routine """

    def __init__(self, main_type: str, other_type: str) -> None:
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


if __name__ == '__main__':
    fs = FileSystem()

    types = read_types(TYPES_LIST_FILE_PATH)
    struct = read_content(STRUCT_FILE_PATH)
    routines = read_routine_templates(ROUTINES_TEMPLATES_DIR_PTAH)
    structs: list[str] = []
    conversions: list[Conversion] = []
    for t in types:
        conversions_heads = []
        c: str = struct
        r = routines[EVERY_TYPE_ROUTINES_FILE_NAME_WITHOUT_EXTENSION]
        r += '\n\n'
        if t.name in routines:
            r = r + '\t' + routines[t.name] + '\n\n'
        # Generate conversions routines here.
        for ot in types:
            if ot.name == t.name:
                continue
            conv: Conversion = Conversion(t.name, ot.name)
            conv.generate()
            conversions.append(conv)
        for conv in conversions:
            if conv.type == t.name:
                r += conv.head + '\n'
        r = r.removesuffix('\n')
        c = c.replace(ROUTINES_PLACEHOLDER_STRING, r)
        c = c.replace(TYPE_NAME_PLACEHOLDER_STRING, t.name)
        c = c.replace(RAW_TYPE_NAME_PLACEHOLDER_STRING, t.raw)
        c = c.replace(DEFAULT_VALUE_PLACEHOLDER_STRING, t.default)
        c += '\n'
        structs.append(c)

    result = ''.join(structs)
    result += '\n'
    for conv in conversions:
        result += conv.body
    result = result.removesuffix('\n\n')
    BODY = read_content(BODY_TEMPLATE_FILE_PATH)
    result = BODY.replace(GENERATE_TYPES_HERE_PLACEHOLDER_STRING, result)
    types_predefine = ''
    for t in types:
        types_predefine += 'struct ' + t.name + ';\n'
    types_predefine = types_predefine.removesuffix('\n')
    result = result.replace(
        PREDEFINE_TYPES_HERE_PLACEHOLDER_STRING, types_predefine)
    result = '// This file is generated by a python script and some templates .\n\n' + result
    result += "\n"
    write_content(OUTPUT_FILE_PATH, result)
