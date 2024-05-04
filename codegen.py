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

    routines: str = ''

    def __init__(self, raw_type_name: str, type_name: str, default_value: str) -> None:
        self.raw: str = raw_type_name
        self.name: str = type_name
        self.default: str = default_value
        self.routines: str = ''

    def public_method(self) -> None:
        """ public method """

    def public_method2(self) -> None:
        """ public method """

    def __str__(self) -> str:
        return self.name  # TODO: Try removing return and see if it works.

    def __repr__(self) -> str:
        return self.name  # TODO: Try removing return and see if it works.

    def __eq__(self, value: object) -> bool:
        return self.name == value

    def __hash__(self) -> int:
        return hash((self.raw, self.name, self.default))


class Conversion:
    """ Conversion Routine """

    every_type_conversion_template_head: str = ''
    every_type_conversion_template_body: str = ''
    conversion_bodies: str = ''

    def __init__(self, main_type: Type, other_type: Type) -> None:
        self.type: str = main_type.name
        self.other: str = other_type.name
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
        self.conversions_templates_dir: str = 'ab/__templates/conversions'

    def read_types(self) -> dict[Type, None]:
        """ Returns a list of dictionaries of types.
        """
        item = read_content(self.types_list_file).split()
        res: dict[Type, None] = {}
        i = 0
        while i < len(item):
            res[Type(item[i], item[i+1], item[i+2])] = None
            i += 3
        return res

    def read_routine_templates(self, types: dict[Type, None]) -> None:
        """ Update routines variables of Type and Types in the list given.
        """
        names = os.listdir(self.routines_templates_dir)
        for name in names:
            path = os.path.join(self.routines_templates_dir, name)
            if os.path.isdir(path):
                continue
            name = name.removesuffix('.hpp')
            content = read_content(path)
            content = content.replace('\n', '\n\t')
            content = content.replace('\n\t\n', '\n\n')
            if name == '_every':
                Type.routines = content
            else:
                for ty in types:
                    if ty == name:
                        ty.routines = content

    def read_conversion_templates(self, types: dict[Type, None]) -> None:
        names = os.listdir(self.conversions_templates_dir)
        for name in names:
            path = os.path.join(self.conversions_templates_dir, name)
            if os.path.isdir(path):
                continue
            name = name.removesuffix('.hpp')
            content = read_content(path).strip()
            content = content.replace('\n', '\n\t')
            content = content.replace('\n\t\n', '\n\n')
            content = content.split('\n', 1)
            head = content[0].strip()
            body = content[1].strip()
            if name == 'every':
                Conversion.every_type_conversion_template_head = head
                Conversion.every_type_conversion_template_head = body

    def read_struct_template(self) -> str:
        """ Returns string of struct template text file
        """
        return read_content(self.struct_template_file)


class Body:
    """ Body Of Code
    """

    def __init__(self, fs: FileSystem) -> None:
        self.types: dict[Type, None] = {}
        self.struct: str = ''
        self.result: str = ''
        self.types = fs.read_types()
        self.struct = fs.read_struct_template()
        fs.read_routine_templates(self.types)
        fs.read_conversion_templates(self.types)

    def __generate_types_predefine(self):
        types_predefine: str = ''
        for t in self.types:
            types_predefine += 'struct ' + t.name + ';\n'
        types_predefine = types_predefine.removesuffix('\n')
        self.result += types_predefine
        self.result += '\n\n'

    def generate(self):
        """ Generate Result
        """
        self.__generate_types_predefine()
        # generate predefine
        # generate structures
        # generate conversion bodies

        structs: list[str] = []
        conversions: list[Conversion] = []
        for t in self.types:
            c: str = self.struct
            r = Type.routines
            r += '\n\n'
            if t.routines != '':
                r = r + '\t' + t.routines + '\n\n'
            # Generate conversions routines here.
            for ot in self.types:
                if ot.name == t.name:
                    continue
                conv: Conversion = Conversion(t, ot)
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

        self.result += ''.join(structs)
        self.result += '\n'
        for conv in conversions:
            self.result += conv.body
        self.result = self.result.removesuffix('\n\n')


class Main:
    """ Main Template """

    def __init__(self) -> None:
        fs = FileSystem()
        body = Body(fs)
        body.generate()
        result = read_content(fs.main_template_file).replace(
            "//_GENERATE_TYPE_HERE", body.result)
        result = '// This file is generated by a python script and some templates .\n\n' + result
        result += "\n"
        write_content(fs.output_file, result)

    def public_method(self) -> None:
        """ public method """

    def public_method_2(self) -> None:
        """ public method """


if __name__ == '__main__':
    main = Main()
