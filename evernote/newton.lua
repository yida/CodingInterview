
b = 0.01

x = 1;

for i = 1, 10 do
  x = x * (2 - b * x)
  print(x)
end
