%Roberto Sergio Ribeiro de Meneses - 520403
%Guilherme Galvao Serra - 520402
functor
export
   andg: AndG 
   org: OrG 
   nandg: NandG 
   norg: NorG 
   xorg: XorG 
   notg: NotG
define
   local
      fun {NotLoop Xs}
         case Xs of X|Xr then (1-X)|{NotLoop Xr} end
      end
   in
   fun {NotG Xs}
      thread {NotLoop Xs} end
   end

   fun {GateMaker F}
      fun {$ Xs Ys}
         fun {GateLoop Xs Ys}
      case Xs#Ys of (X|Xr)#(Y|Yr) then
         {F X Y}|{GateLoop Xr Yr}
      end
         end
      in
         thread {GateLoop Xs Ys} end
      end
   end

   AndG = {GateMaker fun {$ X Y} X*Y end}
   OrG = {GateMaker fun {$ X Y} X+Y-X*Y end}
   NandG = {GateMaker fun {$ X Y} 1-X*Y end}
   NorG = {GateMaker fun {$ X Y} 1-X-Y+X*Y end}
   XorG = {GateMaker fun {$ X Y} X+Y-2*X*Y end}
end