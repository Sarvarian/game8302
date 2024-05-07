""" To generate C math functions directors """

from string import Template


LIST_OF_C_MATH_FUNCTIONS: str = """
pow base exponent
sqrt arg
floor arg
trunc arg
""".strip()


C_MATH_FUNCTION_TEMPLATE = Template("""
inline $type_name cpp_std_$func_name$suffix($typed_args) { return $func_name$suffix($input); }$new_line
""".strip())


def generate_c_math_functions_directors() -> str:
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
