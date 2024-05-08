""" Routines to help you generate methods for types.
"""


from dataclasses import asdict
from string import Template
from code_generation.types import MethodGenerationData, Type


METHOD_TEMPLATE = Template("""
$tab_character$method_return_type $method_name($method_arguments)$const
$tab_character{
$tab_character$tab_character$method_body
$tab_character}$new_line$new_line
""".strip())


def generate_method(data: MethodGenerationData) -> str:
    ''' Generate methods.
    '''
    result = METHOD_TEMPLATE.substitute(asdict(data))
    return result


def generate_arguments(arguments: list[list[str]]) -> str:
    """ Generate a string to use as method_arguments in method generation.
    arguments: have the type of each argument is index 0 of the nested list
                and the argument name as the index 1 of the nested list.
    """
    result = ''
    for arg in arguments:
        result += f'{arg[0]} {arg[1]}, '
    result = result.removesuffix(', ')
    return result


def generate_constructors(ty: Type) -> str:
    """ Generate constructor methods for the given type.
    """
    members = ty.members
    data = MethodGenerationData()
    data.type_name = ty.name
    data.default_value = ty.default
    data.base_type_name = 'Raw'
    data.method_name = data.type_name
    data.method_return_type = ''
    data.const = f' : {members[0]}_({members[0]}) '
    data.method_arguments = f'{data.base_type_name} {', '.join(members)}'
    data.method_body = ''
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
