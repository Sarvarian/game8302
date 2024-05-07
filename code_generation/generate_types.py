""" Generate types for use in code generation. """

from code_generation.types import (Dimension, MethodGenerationData, Type)


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


# def read_routines_template(full_path: str) -> str:
#     """ Read the given address file and returns formatted.
#     """
#     return \
#         read_content(full_path) \
#         .replace('\n', '\n\t') \
#         .replace('\n\t\n', '\n\n')


def read_and_generate_types() -> list[Type]:
    """ As the name suggest.
    """
    # Read vector types templates.
    #
    # vec2_template = read_content(vec2_template_file)
    # vec3_template = read_content(vec3_template_file)
    # vec4_template = read_content(vec4_template_file)
    # vec2_routines = read_routines_template(vec2_routines_file)
    # vec3_routines = read_routines_template(vec3_routines_file)
    # vec4_routines = read_routines_template(vec4_routines_file)

    # # Generate vector types
    # #
    scalar_types = generate_scalar_types()
    vec_types: list[Type] = []
    # for i in range(2, 5):
    #     for comp in scalar_types:
    #         name = f'vec{i}{comp.name}'
    #         vec_template = ''
    #         vec_routines = ''
    #         match i:
    #             case 2:
    #                 vec_template = vec2_template
    #                 vec_routines = vec2_routines
    #             case 3:
    #                 vec_template = vec3_template
    #                 vec_routines = vec3_routines
    #             case 4:
    #                 vec_template = vec4_template
    #                 vec_routines = vec4_routines
    #             case _:
    #                 raise DimensionError()
    #         ty = Type(comp.name, name, comp.default, Dimension(i, 1))
    #         ty.template = vec_template
    #         ty.common_routines = vec_routines
    #         path = os.path.join(routines_templates_dir, f'{name}.hpp')
    #         ty.routines = read_routines_template(path)
    #         vec_types.append(ty)

    return scalar_types + vec_types
