"""" To generate c++ math library code. """

import os
import os.path
from dataclasses import dataclass, asdict
from string import Template


routines_templates_dir: str = 'ab/__templates/routines'
conversions_templates_dir: str = 'ab/__templates/conversions'
vec2_template_file: str = 'ab/__templates/vec2.hpp'
vec3_template_file: str = 'ab/__templates/vec3.hpp'
vec4_template_file: str = 'ab/__templates/vec4.hpp'
vec2_routines_file: str = 'ab/__templates/routines/vec2.hpp'
vec3_routines_file: str = 'ab/__templates/routines/vec3.hpp'
vec4_routines_file: str = 'ab/__templates/routines/vec4.hpp'


STRUCT_BODY_TEMPLATE = Template("""
struct $name
{
public:
$public_area

private:
$private_area
};$new_line$new_line
""".strip())


LIST_OF_C_MATH_FUNCTIONS: str = """
pow base exponent
sqrt arg
floor arg
trunc arg
""".strip()


C_MATH_FUNCTION_TEMPLATE = Template("""
inline $type_name cpp_std_$func_name$suffix($typed_args) { return $func_name$suffix($input); }$new_line
""".strip())


def generate_c_math_functions_director() -> str:
    """ Generate a list of functions that points'
        to c math function.
        (Because... I can't care to explain right now!)
    """
    types = [
        {'name': 'float', 'suffix': 'f'},
        {'name': 'double', 'suffix': ''},
        {'name': 'long double', 'suffix': 'l'},
    ]
    functions = LIST_OF_C_MATH_FUNCTIONS.splitlines()
    functions = map(lambda x: x.strip().split(), functions)

    res = ''
    for func in functions:
        for ty in types:
            type_name = ty['name']
            typed_args = ''
            for text in func:
                if text == func[0]:
                    continue
                typed_args += f' {type_name} {text},'
            typed_args = typed_args.strip().removesuffix(',')
            values: dict[str, str] = {}
            values['type_name'] = type_name
            values['suffix'] = ty['suffix']
            values['func_name'] = func[0]
            values['typed_args'] = typed_args
            values['input'] = typed_args.replace(f'{type_name} ', '')
            values['new_line'] = '\n'
            res += C_MATH_FUNCTION_TEMPLATE.substitute(values)
    res = res.strip()
    return f"""
namespace
{{
{res}
}} // namespace
""".strip() + '\n\n'


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


class DimensionError(Exception):
    """ Dimension Error """

    def __init__(self) -> None:
        super().__init__('type dimension is invalid!')


@dataclass
class Dimension:
    """ Dimension of Data Type
        1 x 1 is scalar
        n x 1 is vector
        n x m is matrix
    """

    i: int
    j: int

    def __init__(self, i: int, j: int):
        self.i = i
        self.j = j
        if i < 1 or j < 1:
            raise DimensionError()

    def is_scalar(self) -> bool:
        """ Check if dimension is 1 x 1
        """
        return self.i == 1 and self.j == 1

    def is_vector(self) -> bool:
        """ Check if dimension is n x 1
        """
        return self.i > 1 and self.j == 1

    def is_matrix(self) -> bool:
        """ Check if dimension is n x m
        """
        return self.i > 1 and self.j > 1


@dataclass
class Type:
    """ Second Version of Type Class """

    name: str
    base: str
    default: str
    dimension: Dimension
    public_area: str = ''
    private_area: str = ''
    new_line: str = '\n'

    def __init__(self, base_tape: str, name: str, default: str, dimension: Dimension) -> None:
        self.base = base_tape
        self.name = name
        self.default = default
        self.dimension = dimension
        self.template = ''
        self.common_routines = ''
        self.routines = ''

    def useless_public_method(self) -> None:
        """ useless public method """

    def useless_public_method_2(self) -> None:
        """ useless public method """


@dataclass
class MethodGenerationData:
    """ Data used for generating constructor methods for types.
    """

    def __init__(self) -> None:
        self.type_name: str = ''
        self.base_type_name: str = ''
        self.default_value: str = ''
        self.member_names_without_suffix_underscore: list[str]


def generate_constructor_methods_for_type(data: MethodGenerationData) -> str:
    """ Generate constructor methods for the given type.
    """
    name = data.type_name
    base = data.base_type_name
    default = data.default_value
    members = data.member_names_without_suffix_underscore
    arguments = ''
    arg_inits = ''
    default_inits = ''
    for member in members:
        arguments += f'{base} {member}, '
        arg_inits += f'{member}_({member}), '
        default_inits += f'{member}_({default}), '
    arguments = arguments.removesuffix(', ')
    arg_inits = arg_inits.removesuffix(', ')
    default_inits = default_inits.removesuffix(', ')
    result = ''
    result += f'\t{name}({arguments}) : {arg_inits} {{}}\n\n'
    result += f'\t{name}() : {default_inits} {{}}\n\n'
    return result


# def generate_addition_and_subtraction_operation_methods(data: MethodGenerationData):
#     """ Generate methods of add and sub for the given type.
#     """
#     name = data.type_name
#     base = data.base_type_name
#     default = data.default_value
#     members = data.member_names_without_suffix_underscore
#     result = ''
#     result += f'\t{name} add({name} rhs) const\n'
#     result += f'\t{{\n'
#     result += f'\t\treturn {name}();\n'
#     result += f'\t}}\n'
#     result += f'\n'
#     result += f'\t{name} add_inplace({name} rhs)\n'
#     result += f'\t{{\n'
#     result += f'\t\r {base}_ =  \n'
#     result += f'\t}}\n\n'


def generate_scalar_template_values(ty: Type) -> None:
    """ Generate body of a type.
    """
    constructor_data: MethodGenerationData = MethodGenerationData()
    constructor_data.type_name = ty.name
    constructor_data.default_value = ty.default
    if ty.dimension.is_scalar():
        constructor_data.base_type_name = 'Raw'
        constructor_data.member_names_without_suffix_underscore = ['value']
        # Generate typedef
        typedef = f'\ttypedef {ty.base} Raw;\n\n'
        constructors = generate_constructor_methods_for_type(constructor_data)
        member = '\tRaw value_;'
        getter = '\n\tRaw raw() const\n\t{\n\t\treturn value_;\n\t}'
        ty.public_area = typedef + constructors + getter
        ty.private_area = member


def generate_float_template_values(float_t: Type) -> None:
    """ Generate template values for float Types
    """
    generate_scalar_template_values(float_t)


def generate_integer_template_values(int_t: Type) -> None:
    """ Generate template values for integer Types
    """
    generate_scalar_template_values(int_t)


def generate_scalar_types() -> list[Type]:
    """ Generate scalar types.
    """
    # Generate float types.
    #
    float_types: list[Type] = []
    float_types.append(Type('float', 'f32', '0.0f', Dimension(1, 1)))
    float_types.append(Type('double', 'f64', '0.0', Dimension(1, 1)))
    # Generate template values:
    list(map(generate_float_template_values, float_types))

    # Generate pointer size types.
    #
    ptr_size_types: list[Type] = []
    ptr_size_types.append(Type('intptr_t', 'isize', '0', Dimension(1, 1)))
    ptr_size_types.append(Type('uintptr_t', 'usize', '0', Dimension(1, 1)))
    # Generate template values:
    list(map(generate_integer_template_values, ptr_size_types))

    # Generate integer types.
    #
    integer_types: list[Type] = []
    # Signed integers:
    bit_number = 8
    while bit_number <= 64:
        ty = Type(f'Sint{bit_number}', f'i{bit_number}', '0', Dimension(1, 1))
        integer_types.append(ty)
        bit_number *= 2
    # Unsigned integers:
    bit_number = 8
    while bit_number <= 64:
        ty = Type(f'Uint{bit_number}', f'u{bit_number}', '0', Dimension(1, 1))
        integer_types.append(ty)
        bit_number *= 2
    # Generate template values:
    list(map(generate_integer_template_values, integer_types))

    return float_types + integer_types + ptr_size_types


def read_and_generate_types() -> list[Type]:
    """ As the name suggest.
    """
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
    scalar_types = generate_scalar_types()
    vec_types: list[Type] = []
    for i in range(2, 5):
        for comp in scalar_types:
            name = f'vec{i}{comp.name}'
            vec_template = ''
            vec_routines = ''
            match i:
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
            ty = Type(comp.name, name, comp.default, Dimension(i, 1))
            ty.template = vec_template
            ty.common_routines = vec_routines
            path = os.path.join(routines_templates_dir, f'{name}.hpp')
            ty.routines = read_routines_template(path)
            vec_types.append(ty)

    return scalar_types + vec_types


class ConversionTemplate:
    """ Conversion Template """

    def __init__(self, head: str, body: str) -> None:
        self.head = head
        self.body = body

    def public_method(self) -> None:
        """ public method """

    def public_method_2(self) -> None:
        """ public method """


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


def placeholder_replacement(t: Type, content: str) -> str:
    """ Whatever the name says.
    """
    result = content
    result = result.replace('//_GENERATE_ROUTINES_HERE', t.routines)
    result = result.replace('_TYPE_NAME', t.name)
    result = result.replace('_RAW_TYPE', t.base)
    result = result.replace('_DEFAULT_VALUE', t.default)
    result = result.replace('_COMP_NAME', t.base)
    return result


def generate_structs(types: list[Type], conversions: list[ConversionTemplate]) -> str:
    """ Generate body of structs for main body.
    """
    result = ''
    for ty in types:
        if not ty.dimension.is_scalar():
            continue
        else:
            result += STRUCT_BODY_TEMPLATE.substitute(asdict(ty))
            continue
        content = ty.template
        if ty.routines != '':
            ty.routines = '\t' + ty.routines + '\n\n'
        ty.routines = ty.common_routines + '\n\n' + ty.routines
        for other in types:
            if other == ty or not other.dimension.is_scalar():
                continue
            for conv in conversions:
                ty.routines += '\t' + conv.head \
                    .replace('_TYPE_NAME', ty.name) \
                    .replace('_OTHER_TYPE', other.name) + '\n'
        ty.routines = ty.routines.removesuffix('\n')
        content = placeholder_replacement(ty, content)
        content += '\n\n'
        result += content
    return result


def generate_conversions_bodies(types: list[Type], conversions: list[ConversionTemplate]) -> str:
    """ Generate Conversions
    """
    result: str = ''
    for base in types:
        if not base.dimension.is_scalar():
            continue
        for other in types:
            if other == base or not other.dimension.is_scalar():
                continue
            for conv in conversions:
                result += conv.body \
                    .replace('_TYPE_NAME', base.name) \
                    .replace('_OTHER_TYPE', other.name) + '\n\n'
    result = result.removesuffix('\n\n')
    return result


def generate_types_predefine(types: list[Type]) -> str:
    """ Types Predefine
    """
    result: str = ''
    for t in types:
        if not t.dimension.is_scalar():
            continue
        result += f'struct {t.name};\n'
    result = result.removesuffix('\n')
    return result


def generate_body() -> str:
    """ Body Of Code
    """
    result: str = ''
    result += generate_c_math_functions_director()
    types = generate_scalar_types()
    conversions = read_conversion_templates()
    result += generate_types_predefine(types)
    result += '\n\n'
    result += generate_structs(types, conversions)
    result += '\n'
    result += generate_conversions_bodies(types, conversions)
    result += '\n'

    result = result.removesuffix('\n')
    return result


def main() -> None:
    """ Main Template
    """
    result = f"""// This file is generated by a python script.\n
#pragma once\n
namespace ab
{{
namespace math
{{\n
{generate_body()}\n
}} // namespace math
}} // namespace ab
"""
    write_content('ab/code_gen_output.hpp', result)
