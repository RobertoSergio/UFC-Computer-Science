defmodule Tree do
  defstruct value: nil, left: nil, right: nil , x: 0 , y: 0

  # Função para criar uma árvore vazia
  def create_empty_tree(value)do
    %Tree{value: value, left: nil, right: nil, x: 0, y: 0}
  end

  def insert_value(nil, value) do
    %Tree{value: value, left: nil, right: nil, y: 0 , x: 0}
  end

  def insert_value(%Tree{} = tree, value) when value < tree.value do
    %Tree{tree | left: insert_value(tree.left, value), y:  0  , x: 0}
  end

  def insert_value(%Tree{} = tree, value) when value > tree.value do
    %Tree{tree | right: insert_value(tree.right, value), y:  0  , x: 0}
  end

  def insert_value(%Tree{} = tree, value) when value == tree.value do
    tree  # Ignorar valores duplicados
  end

  defmacro tree(left: left, right: right) do
    quote do
      %{left: unquote(left), right: unquote(right)}
    end
  end

  def depth_first(tree) do
    case tree do
      %Tree{value: value, x: x, y: y, left: left, right: right} ->
        IO.inspect("Value: #{value}, X: #{x}, Y: #{y}")
        depth_first(left)
        depth_first(right)
      nil ->
        nil
    end
  end

  def calculate_tree_coordinates(nil, _, _,_), do: nil

  def calculate_tree_coordinates(%Tree{} = node, distance, scale, nivel) do
    node = %Tree{node | y: nivel}

    left_node = calculate_tree_coordinates(node.left, distance - scale, scale , nivel+1)
    right_node = calculate_tree_coordinates(node.right, distance + scale, scale , nivel+1)

    case {left_node, right_node} do
      {nil, nil} -> %Tree{node | x: distance,}
      {nil, right} -> %Tree{node | x: distance, right: right}
      {left, nil} -> %Tree{node | x: distance, left: left}
      {left, right} ->
        avg_x = (left.x + right.x) / 2
        %Tree{node | x: avg_x, left: left, right: right}
    end
  end

end


# MAIN
tree1 = Tree.create_empty_tree(10)
tree1 = Tree.insert_value(tree1, 12)
tree1 = Tree.insert_value(tree1, 5)
tree1 = Tree.insert_value(tree1, 2)
tree1 = Tree.insert_value(tree1, 15)
tree1 = Tree.insert_value(tree1, 20)
tree1 = Tree.insert_value(tree1, 6)
tree1 = Tree.insert_value(tree1, 26)
tree1 = Tree.insert_value(tree1, 18)


tree1 = Tree.calculate_tree_coordinates(tree1, 0, 10 , 0)

Tree.depth_first(tree1)
