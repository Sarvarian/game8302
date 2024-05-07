""" Data types use in code generation. """

from dataclasses import dataclass


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
