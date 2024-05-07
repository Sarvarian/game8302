""" Generate the main body final source code. """

import os
import os.path
from dataclasses import asdict
from string import Template

from code_generation.cmath import generate_c_math_functions_directors
from code_generation.generate_types import generate_scalar_types
from code_generation.types import Type

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
    result += generate_c_math_functions_directors()
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
