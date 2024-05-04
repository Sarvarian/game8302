"""" To generate c++ code. """

import os
import os.path


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


class FileSystem:
    """ To Work With Files And Directories """

    def __init__(self) -> None:
        self.output_dir: str = 'ab/'
        self.output_file: str = 'ab/code_gen_output.hpp'
        self.templates_dir: str = 'ab/__templates'
        self.main_template_file: str = 'ab/__templates/math.hpp'
        self.types_list_file: str = 'ab/__templates/types.txt'
        self.struct_template_file: str = 'ab/__templates/struct.hpp'
        self.routines_templates_dir: str = 'ab/__templates/routines'
        self.conversions_dir_name: str = 'ab/__templates/conversions'

    def read_types(self) -> list[Type]:
        """ Returns a list of dictionaries of types.
        """
        item = read_content(self.types_list_file).split()
        res: list[Type] = []
        i = 0
        while i < len(item):
            res.append(Type(item[i], item[i+1], item[i+2]))
            i += 3
        return res

    def read_routine_templates(self) -> dict[str, str]:
        """ Returns a dictionary of types and their routines.
        """
        names = os.listdir(self.routines_templates_dir)
        res: dict[str, str] = {}
        for name in names:
            path = os.path.join(self.routines_templates_dir, name)
            if os.path.isdir(path):
                continue
            name = name.removesuffix('.hpp')
            res[name] = read_content(path)
            res[name] = res[name].replace('\n', '\n\t')
            res[name] = res[name].replace('\n\t\n', '\n\n')
        return res

    def read_struct_template(self) -> str:
        """ Returns string of struct template text file
        """
        return read_content(self.struct_template_file)


if __name__ == '__main__':
    fs = FileSystem()

    types = fs.read_types()
    struct = fs.read_struct_template()
    routines = fs.read_routine_templates()
    structs: list[str] = []
    conversions: list[Conversion] = []
    for t in types:
        conversions_heads = []
        c: str = struct
        r = routines['_every']
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
        c = c.replace('//_GENERATE_ROUTINES_HERE', r)
        c = c.replace('_TYPE_NAME', t.name)
        c = c.replace('_RAW_TYPE', t.raw)
        c = c.replace('_DEFAULT_VALUE', t.default)
        c += '\n'
        structs.append(c)

    result = ''.join(structs)
    result += '\n'
    for conv in conversions:
        result += conv.body
    result = result.removesuffix('\n\n')
    BODY = read_content(fs.main_template_file)
    result = BODY.replace("//_GENERATE_TYPE_HERE", result)
    types_predefine = ''
    for t in types:
        types_predefine += 'struct ' + t.name + ';\n'
    types_predefine = types_predefine.removesuffix('\n')
    result = result.replace('//_PREDEFINE_TYPE_HERE', types_predefine)
    result = '// This file is generated by a python script and some templates .\n\n' + result
    result += "\n"
    write_content(fs.output_file, result)
