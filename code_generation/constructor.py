""" Routines to generate constructors for types.
"""


from code_generation.method import generate_arguments, generate_method
from code_generation.types import MethodGenerationData


def generate_constructor_methods_for_type(data: MethodGenerationData) -> str:
    """ Generate constructor methods for the given type.
    """
    data.method_name = data.type_name
    data.method_return_type = ''
    members = data.member_names_without_suffix_underscore
    arguments: list[list[str]] = []
    arg_inits = ''
    default_inits = ''
    for member in members:
        arguments.append([data.base_type_name, member])
        arg_inits += f'{member}_({member}), '
        default_inits += f'{member}_({data.default_value}), '
    arg_inits = arg_inits.removesuffix(', ')
    default_inits = default_inits.removesuffix(', ')
    data.method_arguments = generate_arguments(arguments)
    data.const = f' : {arg_inits}'
    elements = \
        list(map(lambda x: x.strip(), generate_method(data).splitlines()))
    init_constructor = f'\t{elements[0]} {elements[1]}{elements[3]}\n\n'
    data.const = f' : {default_inits}'
    data.method_arguments = ''
    elements = \
        list(map(lambda x: x.strip(), generate_method(data).splitlines()))
    default_constructor = f'\t{
        elements[0]} {elements[1]}{elements[3]}\n\n'
    return init_constructor + default_constructor
