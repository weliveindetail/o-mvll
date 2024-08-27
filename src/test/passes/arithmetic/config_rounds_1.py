import omvll
from functools import lru_cache

#import debugpy
#debugpy.listen(('0.0.0.0', 5678))
print("Python API waiting for debugger. Attach to 0.0.0.0:5678 to proceed.")
#debugpy.wait_for_client()
#debugpy.breakpoint()

class MyConfig(omvll.ObfuscationConfig):
    def __init__(self):
        super().__init__()
    def obfuscate_arithmetic(self, mod: omvll.Module,
                                   fun: omvll.Function) -> omvll.ArithmeticOpt:
        return omvll.ArithmeticOpt(rounds=1)

@lru_cache(maxsize=1)
def omvll_get_config() -> omvll.ObfuscationConfig:
    return MyConfig()
