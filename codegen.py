"""" To generate c++ code. """

import os
import os.path


output_dir: str = 'ab/'
output_file: str = 'ab/code_gen_output.hpp'
templates_dir: str = 'ab/__templates'
main_template_file: str = 'ab/__templates/math.hpp'
types_list_file: str = 'ab/__templates/types.txt'
struct_template_file: str = 'ab/__templates/struct.hpp'
routines_templates_dir: str = 'ab/__templates/routines'
conversions_templates_dir: str = 'ab/__templates/conversions'
vec2_template_file: str = 'ab/__templates/vec2'
vec3_template_file: str = 'ab/__templates/vec3'
vec4_template_file: str = 'ab/__templates/vec4'


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


class ConversionTemplate:
    """ Conversion Template """

    def __init__(self, head: str, body: str) -> None:
        self.head = head
        self.body = body

    def public_method(self) -> None:
        """ public method """

    def public_method_2(self) -> None:
        """ public method """


def read_types() -> dict[Type, None]:
    """ Returns a list of dictionaries of types.
    """
    item = read_content(types_list_file).split()
    res: dict[Type, None] = {}
    i = 0
    while i < len(item):
        res[Type(item[i], item[i+1], item[i+2])] = None
        i += 3
    return res


def read_routine_templates(types: dict[Type, None]) -> None:
    """ Update routines variables of Type and Types in the list given.
    """
    names = os.listdir(routines_templates_dir)
    for name in names:
        path = os.path.join(routines_templates_dir, name)
        if os.path.isdir(path):
            continue
        name = name.removesuffix('.hpp')
        content = read_content(path)
        content = content.replace('\n', '\n\t')
        content = content.replace('\n\t\n', '\n\n')
        if name == '_every':
            Type.routines = content
        else:
            for t in types:
                if t.name == name:
                    t.routines = content


def read_conversion_templates() -> list[ConversionTemplate]:
    """ Returns list of conversion templates
    """
    names = os.listdir(conversions_templates_dir)
    templates: list[ConversionTemplate] = []
    for name in names:
        path = os.path.join(conversions_templates_dir, name)
        if os.path.isdir(path):
            continue
        name = name.removesuffix('.hpp')
        content = read_content(path).strip()
        content = content.replace('\n\t\n', '\n\n')
        content = content.split('\n', 1)
        head = content[0].strip()
        body = content[1].strip()
        templates.append(ConversionTemplate(head, body))
    return templates


class ConversionGenerator:
    """ Conversion Routine """

    def __init__(self, templates: list[ConversionTemplate]) -> None:
        self.templates: list[ConversionTemplate] = templates
        self.type: Type
        self.other: Type

    def __replace(self, text: str) -> str:
        return text.replace('_TYPE_NAME', self.type.name).replace('_OTHER_TYPE', self.other.name)

    def generate_head(self) -> str:
        """ Generate head of conversion routine. """
        result = ''
        for template in self.templates:
            result += '\t' + self.__replace(template.head)
        return result

    def generate_body(self) -> str:
        """ Generate body of conversion routine. """
        result = ''
        for template in self.templates:
            result = self.__replace(template.body) + '\n\n'
        return result


def generate_structs(types: dict[Type, None], conversion_generator: ConversionGenerator) -> str:
    """ Structs
    """
    struct: str = ''
    struct = read_content(struct_template_file)
    result = ''
    for t in types:
        c: str = struct
        r = Type.routines
        r += '\n\n'
        if t.routines != '':
            r = r + '\t' + t.routines + '\n\n'
        conversion_generator.type = t
        for ot in types:
            if t == ot:
                continue
            conversion_generator.other = ot
            r += conversion_generator.generate_head() + '\n'
        r = r.removesuffix('\n')
        c = c.replace('//_GENERATE_ROUTINES_HERE', r)
        c = c.replace('_TYPE_NAME', t.name)
        c = c.replace('_RAW_TYPE', t.raw)
        c = c.replace('_DEFAULT_VALUE', t.default)
        c += '\n\n'
        result += c
    result += '\n'
    return result


def generate_conversions(types: dict[Type, None], conversion_generator: ConversionGenerator) -> str:
    """ Generate Conversions
    """
    result: str = ''
    for t in types:
        conversion_generator.type = t
        for ot in types:
            if t == ot:
                continue
            conversion_generator.other = ot
            result += conversion_generator.generate_body()
    result = result.removesuffix('\n\n')
    return result


def generate_types_predefine(types: dict[Type, None]) -> str:
    """ Types Predefine
    """
    result: str = ''
    for t in types:
        result += f'struct {t.name};\n'
    result = result.removesuffix('\n')
    result += '\n\n'
    return result


def generate_body() -> str:
    """ Body Of Code
    """
    types: dict[Type, None] = {}
    types = read_types()
    read_routine_templates(types)
    conversion_generator = ConversionGenerator(read_conversion_templates())
    result: str = ''
    result += generate_types_predefine(types)
    result += generate_structs(types, conversion_generator)
    result += generate_conversions(types, conversion_generator)
    # generate vector types
    return result


def main() -> None:
    """ Main Template
    """
    result = read_content(main_template_file).replace(
        "//_GENERATE_TYPE_HERE", generate_body())
    result = '// This file is generated by a python script and some templates .\n\n' + result
    result += "\n"
    write_content(output_file, result)


if __name__ == '__main__':
    main()
