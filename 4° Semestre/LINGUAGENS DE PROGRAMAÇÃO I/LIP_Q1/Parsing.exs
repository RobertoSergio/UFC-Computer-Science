defmodule MyParser do
  defmodule ParserError do
    defexception message: "Parser error"
  end

  defmodule Record do
    defstruct program: nil,
               if: nil,
               while: nil,
               read: nil,
               write: nil,
               assign: nil
  end

  def parse_program(tokens) do
    {s1, s_n} = parse_prog(tokens, [])
    {s1, s_n}
  end

  defp parse_prog(["program" | s2] = s1, s_n) do
    {y, s3} = parse_id(s2, [])
    s3 = [";" | s4]
    {z, s5} = parse_stat(s4, [])
    s5 = ["end" | s_n]
    {:ok, %Record.program{program: y}, s5}
  end

  defp parse_stat(["begin" | s2] = s1, s_n) do
    {x1, s3} = parse_sequence(s2, &parse_stat/2, fn _ -> true end, s_n)
    {:ok, %Record.program{program: x1}, s3}
  end

  defp parse_stat(["if" | s2] = s1, s_n) do
    {c, s3} = parse_comp(s2, [])
    s3 = ["then" | s4]
    {x1, s5} = parse_stat(s4, [])
    s5 = ["else" | s6]
    {x2, s_n} = parse_stat(s6, [])
    {:ok, %Record.if{if: c, then: x1, else: x2}, s_n}
  end

  defp parse_stat(["while" | s2] = s1, s_n) do
    {c, s3} = parse_comp(s2, [])
    s3 = ["do" | s4]
    {x, s_n} = parse_stat(s4, [])
    {:ok, %Record.while{while: c, do: x}, s_n}
  end

  defp parse_stat(["read" | s2] = s1, s_n) do
    {i, s_n} = parse_id(s2, [])
    {:ok, %Record.read{read: i}, s_n}
  end

  defp parse_stat(["write" | s2] = s1, s_n) do
    {e, s_n} = parse_expr(s2, [])
    {:ok, %Record.write{write: e}, s_n}
  end

  defp parse_stat([t | s3] = s1, s_n) when is_atom(t) do
    s2 = [":=" | s3]
    {e, s_n} = parse_expr(s2, [])
    {:ok, %Record.assign{assign: t, value: e}, s_n}
  end

  defp parse_stat(s1, _s_n) do
    raise ParserError, message: "Unexpected token in statement"
  end

  defp parse_sequence(s1, non_term, sep, s_n) do
    {x1, s2} = non_term.(s1, s_n)
    if sep.(hd(s2)) do
      {x2, s_n} = parse_sequence(tl(s2), non_term, sep, s_n)
      {x1, s_n}
    else
      {x1, s_n}
    end
  end

  defp parse_comp(s1, s_n) do
    {x1, s2} = parse_sequence(s1, &is_comp_op/1, s_n)
    {x1, s2}
  end

  defp parse_expr(s1, s_n) do
    {x1, s2} = parse_sequence(s1, &is_expr_op/1, s_n)
    {x1, s2}
  end

  defp parse_term(s1, s_n) do
    {x1, s2} = parse_sequence(s1, &is_term_op/1, s_n)
    {x1, s2}
  end

  defp parse_fact([t | s2], s_n) do
    if is_integer(t) or is_atom(t) do
      {t, s2}
    else
      ["(" | s1] = s2
      {e, [")" | s3]} = parse_expr(s1, s_n)
      {e, s3}
    end
  end

  defp parse_id([x | s1], s_n) when is_atom(x) do
    {x, s1}
  end

  defp is_comp_op(y) do
    y in ["<", ">", "=<", ">=", "==", "!="]
  end

  defp is_expr_op(y) do
    y in ["+", "-"]
  end

  defp is_term_op(y) do
    y in ["*", "/"]
  end

  defp is_int(x) do
    is_integer(x)
  end
end

# Main:
tokens = ["program", :foo, ";", "begin", "while", :a, "+", 3, "<", :b, "do", :b, ":=", :b, "+", 1, "end"]
{:ok, parsed_output, _} = MyParser.parse_program(tokens)
IO.inspect(parsed_output)
