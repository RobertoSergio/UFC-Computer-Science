% Sequential Stateful Model with short-circuiting
%Roberto Sergio Ribeiro de Meneses - 520403
%Guilherme Galvao Serra - 520402
declare
fun {JosephusSeq N K}
   A = {NewArray N nil}
   Ultimo
in
   for I in 1..N do
      A.I = {NewCell {NewCell I K} true}
   end
   Ultimo = A.N
   for I in 1..N-1 do
      {A.I.2} := A.(I+1)
   end
   {A.N.2} := A.1

   local
      fun {Matar X S I}
         if S == 1 then Ultimo = I
         elseif X mod K == 0 then
            if {A.I.2.2} > 0 then
               {A.I.2.2} := {A.I.2.2} - 1
               {Matar X+1 S-1 I}
            else
               skip  % Pula a chamada recursiva quando não for mais necessário.
            end
         else
            {Matar X+1 S I}
         end
      end
   in
      {Matar 1 N 1 Ultimo}
   end
   Ultimo
end