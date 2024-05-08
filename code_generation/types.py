""" Data types for use in code generation. """

from dataclasses import dataclass


class DimensionError(Exception):
    """ Dimension Error """

    def __init__(self) -> None:
        super().__init__('type dimension is invalid!.')


class UnhandledCase(Exception):
    """ Unhandled Case """

    def __init__(self) -> None:
        super().__init__('Case for a clause in a condition is not handled.')


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

    def generate_member_names(self) -> list[str]:
        """ Generate member names for types
        that use this dimension.
        Without suffix underscore.
        """
        if self.is_scalar():
            return ['value']
        if self.is_vector():
            names = ['x', 'y', 'z', 'w']
            if self.i > len(names):
                raise UnhandledCase()
            result: list[str] = []
            for i in range(self.i):
                result.append(names[i])
            return result
        if self.is_matrix():
            raise UnhandledCase()
        raise UnhandledCase()


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
        self.members: list[str] = dimension.generate_member_names()

    def useless_public_method(self) -> None:
        """ useless public method """

    def useless_public_method_2(self) -> None:
        """ useless public method """


@dataclass
class MethodGenerationData:
    """ Data used for generating methods for types.
    """
    type_name: str = ''
    base_type_name: str = ''
    default_value: str = ''
    method_name: str = ''
    method_return_type: str = ''
    const: str = ''
    method_arguments: str = ''
    method_body: str = ''
    tab_character: str = '\t'
    new_line: str = '\n'

    def __init__(self, ty: Type):
        self.type_name = ty.name
        self.base_type_name = ty.base
        self.default_value = ty.default
