from enum import Enum
from multiprocessing import Value
import struct

# id_value: int, timer_value: float, temperature_value: float, cg: float


class EcFlexTypes(Enum):
     ID = ('id', 'i')
     TIMER = ('timer', 'i')
     TEMPERATURE = ('temperature', 'i')
     GLUCOSE_CONCENTRATION = ('glucose_concentration', 'f')


     @classmethod
     def from_name(cls, name: str):
          for i in EcFlexTypes:
               if i.value[0] == name:
                    return i
          return None

     def data_type(elem: "EcFlexTypes"):
          return elem.value[1]
          

class EcFlexValues():
     def __init__(self) -> None:
          self.values = {} # ECfelType -> Value(type, value

     def __getitem__(self, id: EcFlexTypes):
          return self.values[id]

     def __setitem__(self, id: EcFlexTypes, value: "Any"):
          self.values[id] = Value(id.data_type(), value)

     def to_bytes(self):
          frmt = ''
          b = b''
          for k in EcFlexTypes:
               if k in self.values:
                    frmt += k.data_type()
                    b += struct.pack(k.data_type(), self.values[k].value)        
          return b