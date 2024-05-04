"""" To generate c++ code. """

import os
from helper import read_types

TEMPLATES_DIR = 'ab/__templates'
OUTPUT_DIR = 'ab/'

BODY_TEMPLATE_FILE = 'math.hpp'
BODY_REPLACEMENT_STRING = '//_GENERATE_CODE_HERE'

TYPES_LIST_FILE_NAME = 'types.txt'
TYPES_LIST_FILE_PATH = os.path.join(TEMPLATES_DIR, TYPES_LIST_FILE_NAME)

if __name__ == '__main__':
    types = read_types(TYPES_LIST_FILE_PATH)
    print(types)
