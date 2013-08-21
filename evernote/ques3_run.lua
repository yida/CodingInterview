
filename = arg[1]
input_file = io.open(filename, 'r')

N = input_file:read('*number')

product = 1
number = {}
for i = 1, N do
  num = input_file:read('*number')
  product = product * num;
  number[#number + 1] = num;
end

print(string.format("product %d", product));
for i = 1, N do
  print(string.format("%d", product / number[i]));
end
