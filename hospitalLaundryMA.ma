[top]
components : hospital@Hospital
components : Laundromat

out : shortAmount shipped dirty

Link : dirty@hospital dirty@Laundromat
Link : shipped@Laundromat clean@hospital
Link : shortAmount@Laundromat shortAmount
Link : shipped@Laundromat shipped
Link : dirty@hospital dirty

[hospital]
distribution : normal
mean : 500
deviation : 200 
shippingTime : 16:00:00:000
cleanTime : 8:10:00:000
amountClean : 0
amountDirty : 0

[Laundromat]
components : laundryCleaning@LaundryCleaning
components : laundryShipping@LaundryShipping 
in : dirty
out : shipped shortAmount
Link : dirty dirty@laundryCleaning
Link : clean@laundryCleaning clean@laundryShipping
Link : shipped@laundryShipping shipped
Link : shortAmount@laundryShipping shortAmount

[laundryCleaning]
cleaningTime : 01:00:00:000
cleaningLoad : 1000
amountDirty : 0

[laundryShipping]
shippingTime : 08:00:00:000 
shippingAmount : 500
amountClean : 1000
