[top]
components : laundryCleaning@LaundryCleaning 
out : clean
in : dirty
Link : dirty dirty@LaundryCleaning
Link : clean@LaundryCleaning clean

[laundryCleaning]
cleaningTime : 01:00:00:000
cleaningLoad : 1000
amountDirty : 500 
