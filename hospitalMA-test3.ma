[top]
components : hospital@Hospital 
out : dirty
in : clean
Link : clean clean@hospital
Link : dirty@hospital dirty

[hospital]
distribution : normal
mean : 500
deviation : 5 
shippingTime : 16:00:00:000
cleanTime : 8:00:00:000
amountClean : 0
amountDirty : 0
