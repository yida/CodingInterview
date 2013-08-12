close all;

fid = fopen('tree', 'r');
[A, count] = fscanf(fid, '%f %f %d %d');

range = [1000000.0, 1000000.0];

x_range = [0, 1000000.0];
y_range = [0, 1000000.0];

figure; 
hold on;
counter = 1;
for node_index = 1 : 4 : 40
  x = A(node_index);
  y = A(node_index + 1);
  dimension = A(node_index + 2);
  id = A(node_index + 3);
  plot(x, y, '*');

  if dimension == 0
    if mod(counter, 2) == 0
      plot([x, x], [0, y]);
    else
      plot([x, x], [y, range(dimension + 1)]);
    end
  elseif dimension == 1
    if mod(counter, 2) == 0
      plot([0, x], [y, y]);
    else
      plot([x, range(dimension + 1)], [y, y]);
    end
  end
  counter = counter + 1;
end

grid on;
axis([0, range(1), 0, range(2)]);
