import _parent


class Child(_parent.Parent):
    def foo(self):
        print(id(self))


c1 = Child()
print("Created child:", id(c1))
