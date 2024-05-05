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
every_type_routines_file: str = 'ab/__templates/routines/_every.hpp'
conversions_templates_dir: str = 'ab/__templates/conversions'
vec2_template_file: str = 'ab/__templates/vec2'
vec3_template_file: str = 'ab/__templates/vec3'
vec4_template_file: str = 'ab/__templates/vec4'
vec2_routines_file: str = 'ab/__templates/routines/vec2'
vec3_routines_file: str = 'ab/__templates/routines/vec3'
vec4_routines_file: str = 'ab/__templates/routines/vec4'


def read_content(file_path: str) -> str:
    """Returns content of a text file if file exist, otherwise returns empty string.
    file_path: Give a full path. (relative or absolute does not matter.)
    """
    if os.path.exists(file_path):
        with open(file_path, 'rt', encoding='utf-8') as file:
            content = file.read().strip()
            file.close()
            return content
    else:
        return ''


def write_content(file_path: str, content: str) -> None:
    """Write content to a text file.
    file_path: Give a full path. (relative or absolute does not matter.)
    content: String of text.
    """
    with open(file_path, 'w', encoding='utf-8', newline='\n') as file:
        file.write(content)
        file.close()


def read_routines_template(full_path: str) -> str:
    """ Read the given address file and returns formatted.
    """
    return \
        read_content(full_path) \
        .replace('\n', '\n\t') \
        .replace('\n\t\n', '\n\n')


class TypeII:
    """ Second Version of Type Class """

    def __init__(self, raw: str, comp: str, name: str, default: str) -> None:
        self.raw = raw
        self.comp = comp
        self.name = name
        self.default = default
        self.template = ''
        self.common_routines = ''
        self.routines = ''

    def public_method(self) -> None:
        """ public method """

    def public_method_2(self) -> None:
        """ public method """


class DimensionError(Exception):
    """ Dimension Error """

    def __init__(self) -> None:
        super().__init__('type dimension should not get any other then these numbers!')


def read_and_generate_types() -> list[TypeII]:
    """ As the name suggest.
    """

    # Read common templates.
    #
    common_template = read_content(struct_template_file)
    common_routines = read_routines_template(every_type_routines_file)

    # Read types.
    #
    basic_types_database = read_content(types_list_file).split()
    types: list[TypeII] = []
    i = 0
    while i < len(basic_types_database):
        raw = basic_types_database[i]
        name = basic_types_database[i + 1]
        default = basic_types_database[i+2]
        ty = TypeII(raw, '', name, default)
        path = os.path.join(routines_templates_dir, f'{ty.name}.hpp')
        ty.routines = read_routines_template(path)
        ty.template = common_template
        ty.common_routines = common_routines
        path = os.path.join(routines_templates_dir, name)
        ty.routines = read_routines_template(path)
        types.append(ty)
        i += 3

    # Read vector types templates.
    #
    vec2_template = read_content(vec2_template_file)
    vec3_template = read_content(vec3_template_file)
    vec4_template = read_content(vec4_template_file)
    vec2_routines = read_routines_template(vec2_routines_file)
    vec3_routines = read_routines_template(vec3_routines_file)
    vec4_routines = read_routines_template(vec4_routines_file)

    # Generate vector types
    #
    vec_types: list[TypeII] = []
    for dimension in range(2, 5):
        for comp in types:
            name = f'vec{dimension}{comp}'
            vec_template = ''
            vec_routines = ''
            match dimension:
                case 2:
                    vec_template = vec2_template
                    vec_routines = vec2_routines
                case 3:
                    vec_template = vec3_template
                    vec_routines = vec3_routines
                case 4:
                    vec_template = vec4_template
                    vec_routines = vec4_routines
                case _:
                    raise DimensionError()
            ty = TypeII(comp.raw, comp.name, name, comp.default)
            ty.template = vec_template
            ty.common_routines = vec_routines
            path = os.path.join(routines_templates_dir, name)
            ty.routines = read_routines_template(path)
            vec_types.append(ty)

    return types + vec_types


class ConversionTemplate:
    """ Conversion Template """

    def __init__(self, head: str, body: str) -> None:
        self.head = head
        self.body = body

    def public_method(self) -> None:
        """ public method """

    def public_method_2(self) -> None:
        """ public method """


class Type:
    """ Just Type """

    template: str = ''
    routines: str = ''

    def __init__(self, raw_type_name: str, type_name: str, default_value: str) -> None:
        self.raw: str = raw_type_name
        self.name: str = type_name
        self.default: str = default_value
        self.routines: str = ''

    def get_type_name(self) -> str:
        """ Whatever this is!!! """
        return self.name

    def get_full_type_name(self) -> str:
        """ Whatever this is!!! """
        return self.get_type_name()

    def public_method(self) -> None:
        """ public method """

    def public_method2(self) -> None:
        """ public method """


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


def generate_routine(self: Type, types: list[Type],
                     conversion_generator: ConversionGenerator) -> None:
    """ Whatever this is!!! """
    if self.routines != '':
        self.routines = '\t' + self.routines + '\n\n'
    self.routines = Type.routines + '\n\n' + self.routines
    conversion_generator.type = self
    for ot in types:
        if self == ot:
            continue
        conversion_generator.other = ot
        self.routines += conversion_generator.generate_head() + '\n'
    self.routines = self.routines.removesuffix('\n')


class VectorType(Type):
    """ Vector Type """

    def __init__(self, component_type: Type, dimensions: int) -> None:
        super().__init__(component_type.raw, component_type.name, component_type.default)
        self.dimensions: int = dimensions
        full_type_name = f'vec{self.dimensions}{self.name}'
        path = os.path.join(routines_templates_dir, f'{full_type_name}.hpp')
        self.routines = read_content(path)

    def get_full_type_name(self) -> str:
        """ Whatever the name says.
        """
        return f"vec{self.dimensions}{self.name}"

    def public_method(self) -> None:
        """ public method """

    def public_method_2(self) -> None:
        """ public method """


class Vec2Type(VectorType):
    """ 2D Vector Type """

    template = ''
    routines = ''

    def __init__(self, component_type: Type) -> None:
        super().__init__(component_type, 2)

    def public_method(self) -> None:
        """ public method """

    def public_method_2(self) -> None:
        """ public method """


class Vec3Type(VectorType):
    """ 2D Vector Type """

    template = ''
    routines = ''

    def __init__(self, component_type: Type) -> None:
        super().__init__(component_type, 3)

    def public_method(self) -> None:
        """ public method """

    def public_method_2(self) -> None:
        """ public method """


class Vec4Type(VectorType):
    """ 2D Vector Type """

    template = ''
    routines = ''

    def __init__(self, component_type: Type) -> None:
        super().__init__(component_type, 4)

    def public_method(self) -> None:
        """ public method """

    def public_method_2(self) -> None:
        """ public method """


def format_routines_template(temp: str) -> str:
    """ Whatever this is!!!
    """
    return temp.replace('\n', '\n\t').replace('\n\t\n', '\n\n')


def read_types() -> list[Type]:
    """ Returns a list of dictionaries of types.
    """

    Type.routines = format_routines_template(
        read_content(every_type_routines_file))

    item = read_content(types_list_file).split()
    types: list[Type] = []
    i = 0
    while i < len(item):
        t = Type(item[i], item[i+1], item[i+2])
        path = os.path.join(routines_templates_dir, f'{t.name}.hpp')
        t.routines = format_routines_template(read_content(path))
        types.append(t)
        i += 3

    vec_types: list[Type] = []
    Vec2Type.routines = format_routines_template(
        read_content(vec2_template_file))
    Vec3Type.routines = format_routines_template(
        read_content(vec3_template_file))
    Vec4Type.routines = format_routines_template(
        read_content(vec4_template_file))

    for dimension in range(2, 5):
        for t in types:
            match dimension:
                case 2: vec_types.append(Vec2Type(t))
                case 3: vec_types.append(Vec3Type(t))
                case 4: vec_types.append(Vec4Type(t))
                case _: raise DimensionError()

    return types + vec_types


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


def struct_replacement(t: Type, content: str) -> str:
    """ Whatever the name says.
    """
    result = content
    result = result.replace('//_GENERATE_ROUTINES_HERE', t.routines)
    result = result.replace('_TYPE_NAME', t.name)
    result = result.replace('_RAW_TYPE', t.raw)
    result = result.replace('_DEFAULT_VALUE', t.default)
    return result


def generate_structs(types: list[Type], conversion_generator: ConversionGenerator) -> str:
    """ Structs
    """
    struct: str = ''
    struct = read_content(struct_template_file)
    result = ''
    for t in types:
        c: str = struct
        if t.routines != '':
            t.routines = '\t' + t.routines + '\n\n'
        t.routines = Type.routines + '\n\n' + t.routines
        conversion_generator.type = t
        for ot in types:
            if t == ot:
                continue
            conversion_generator.other = ot
            t.routines += conversion_generator.generate_head() + '\n'
        t.routines = t.routines.removesuffix('\n')
        c = struct_replacement(t, c)
        c += '\n\n'
        result += c
    return result


def generate_conversions(types: list[Type], conversion_generator: ConversionGenerator) -> str:
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


def generate_types_predefine(types: list[Type]) -> str:
    """ Types Predefine
    """
    result: str = ''
    for t in types:
        result += f'struct {t.get_full_type_name()};\n'
    result = result.removesuffix('\n')
    return result


# def generate_vector_types_predefine(types: list[VectorType]) -> str:
#     """ Whatever the name says.
#     """
#     res = ''
#     for t in types:
#         res += f"struct {t.get_full_type_name()};\n"
#     return res


# def generate_vector_structs(types: list[VectorType]) -> str:
#     """ Whatever the name says.
#     """
#     result: str = ''

#     for t in types:

    # if t.routines

    # struct: str = ''
    # struct = read_content(struct_template_file)
    # result = ''
    # for t in types:
    #     c: str = struct
    #     if t.routines != '':
    #         t.routines = '\t' + t.routines + '\n\n'
    #     t.routines = Type.routines + '\n\n' + t.routines
    #     conversion_generator.type = t
    #     for o_t in types:
    #         if t == o_t:
    #             continue
    #         conversion_generator.other = o_t
    #         t.routines += conversion_generator.generate_head() + '\n'
    #     t.routines = t.routines.removesuffix('\n')
    #     c = struct_replacement(t, c)
    #     c += '\n\n'
    #     result += c
    # return result


def generate_body() -> str:
    """ Body Of Code
    """
    types = read_types()
    conversion_generator = ConversionGenerator(read_conversion_templates())
    result: str = ''
    result += generate_types_predefine(types)
    result += '\n\n'
    result += generate_structs(types, conversion_generator)
    result += '\n'
    result += generate_conversions(types, conversion_generator)
    result += '\n\n\n'
    # result += generate_vector_types_predefine(vector_types)
    # result += generate_vector_structs(vector_types)

    result = result.removesuffix('\n')
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
