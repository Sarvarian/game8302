""" Routines to generate constructors for types.
"""


from code_generation.method import generate_method
from code_generation.types import MethodGenerationData


def generate_constructor_methods_for_type(data: MethodGenerationData) -> str:
    """ Generate constructor methods for the given type.
    """
    members = data.member_names_without_suffix_underscore
    data.method_name = data.type_name
    data.method_return_type = ''
    data.const = f' : {members[0]}_({members[0]}) '
    data.method_arguments = f'{data.base_type_name} {', '.join(members)}'
    init_constructor = \
        generate_method(data) \
        .replace('\t ', '\t') \
        .replace('\n\t{\n\t\t\n\t}', '{}')
    s = f'_({data.default_value}), '
    data.const = f' : {s.join(members)}{s.removesuffix(', ')} '
    data.method_arguments = ''
    default_constructor = \
        generate_method(data) \
        .replace('\t ', '\t') \
        .replace('\n\t{\n\t\t\n\t}', '{}')
    return init_constructor + default_constructor
