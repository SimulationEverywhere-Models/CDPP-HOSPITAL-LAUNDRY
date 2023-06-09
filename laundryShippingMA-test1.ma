[top]
components : laundryShipping@LaundryShipping 
out : shipped shortAmount
in : clean
Link : clean clean@laundryShipping
Link : shipped@laundryShipping shipped
Link : shortAmount@laundryShipping shortAmount

[laundryShipping]
shippingTime : 08:00:00:000 
shippingAmount : 500
amountClean : 500
