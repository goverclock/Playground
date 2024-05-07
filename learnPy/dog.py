class Dog:
    """yes, a dog"""
    def __init__(self, name, age):
        self.name = name
        self.age = age
    def sit(self):
        print(f'{self.name} is now sitting.')
    def roll(self):
        print(f'{self.name} is now rolling.')

class BetterDog(Dog):
    """crap"""
    def __init__(self, lol):
        super().__init__(lol, 'yeah')
        self.lol = lol


