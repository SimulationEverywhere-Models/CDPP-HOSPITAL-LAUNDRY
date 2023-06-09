[top]
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
amountClean : 0
