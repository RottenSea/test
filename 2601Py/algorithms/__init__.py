from .abc import ABC
from .fa import FA
from .pgsa import PGSA
from .cs import CS
from .ba import BA
from .fpa import FPA
from .gwo import GWO
from .da import DA
from .eho import EHO
from .woa import WOA

ALGORITHMS = {
    'ABC': ABC,
    'FA': FA,
    'PGSA': PGSA,
    'CS': CS,
    'BA': BA,
    'FPA': FPA,
    'GWO': GWO,
    'DA': DA,
    'EHO': EHO,
    'WOA': WOA,
}
