def obj(value):
	return {'val':value}
 
 
a = [obj(1),obj(2),obj(3)]
b = a
b[1] = obj(42)
print(a)
 
print("copy via extend")
a = [obj(1),obj(2),obj(3)]
b = []
b.extend(a)
print(b)
b[1] = obj(42)
print(b)
print(a)
b[2]["val"] = 123
print(b)
print(a)
 
print("copy via method")
a = [obj(1),obj(2),obj(3)]
b = a.copy()
print(b)
b[1] = obj(42)
print(b)
print(a)
b[2]["val"] = 123
print(b)
print(a)
 
import copy
print("copy via deepcopy")
a = [obj(1),obj(2),obj(3)]
b = copy.deepcopy(a)
print(b)
b[1] = obj(42)
print(b)
print(a)
b[2]["val"] = 123
print(b)
print(a)
 
import copy
print("copy via shallow copy")
a = [obj(1),obj(2),obj(3)]
b = copy.copy(a)
print(b)
b[1] = obj(42)
print(b)
print(a)
b[2]["val"] = 123
print(b)
print(a)