"""" To generate c++ code. """

import os.path
from helper import read_content, read_types, write_content, read_routine_templates

TEMPLATES_DIR = 'ab/__templates'
OUTPUT_DIR = 'ab/'
OUTPUT_FILE_NAME = 'code_gen_output.hpp'
OUTPUT_FILE_PATH = os.path.join(OUTPUT_DIR, OUTPUT_FILE_NAME)

BODY_TEMPLATE_FILE_NAME = 'math.hpp'
BODY_TEMPLATE_FILE_PATH = os.path.join(TEMPLATES_DIR, BODY_TEMPLATE_FILE_NAME)

BODY_PLACEHOLDER_STRING = '//_GENERATE_CODE_HERE'

TYPES_LIST_FILE_NAME = 'types.txt'
TYPES_LIST_FILE_PATH = os.path.join(TEMPLATES_DIR, TYPES_LIST_FILE_NAME)

STRUCT_FILE_NAME = 'struct.hpp'
STRUCT_FILE_PATH = os.path.join(TEMPLATES_DIR, STRUCT_FILE_NAME)

ROUTINES_PLACEHOLDER_STRING = '//_GENERATE_ROUTINES_HERE'
TYPE_NAME_PLACEHOLDER_STRING = '_TYPE_NAME'
RAW_TYPE_NAME_PLACEHOLDER_STRING = '_RAW_TYPE'
DEFAULT_VALUE_PLACEHOLDER_STRING = '_DEFAULT_VALUE'

ROUTINES_TEMPLATES_DIR_NAME = 'routines'
ROUTINES_TEMPLATES_DIR_PTAH = os.path.join(
    TEMPLATES_DIR, ROUTINES_TEMPLATES_DIR_NAME)


if __name__ == '__main__':
    types = read_types(TYPES_LIST_FILE_PATH)
    struct = read_content(STRUCT_FILE_PATH)
    routines = read_routine_templates(ROUTINES_TEMPLATES_DIR_PTAH)
    res = []
    for t in types:
        c = struct.replace(TYPE_NAME_PLACEHOLDER_STRING, t['type'])
        c = c.replace(RAW_TYPE_NAME_PLACEHOLDER_STRING, t['raw'])
        res.append(c)
    RES = ''.join(res)
    BODY = read_content(BODY_TEMPLATE_FILE_PATH)
    RES = BODY.replace(BODY_PLACEHOLDER_STRING, RES)
    write_content(OUTPUT_FILE_PATH, RES)
