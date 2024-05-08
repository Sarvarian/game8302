""" Routines to help you generate methods for types.
"""


from dataclasses import asdict
from string import Template
from code_generation.types import MethodGenerationData


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
