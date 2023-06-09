This document describes the various batch files distributed with this project.

** hospitalLaundry.bat **
This batch file implements the final hospital laundry simulator using a coupled
laundromat model and atomic hospital model. It uses hospitalLaundyMA.ma and hospitalLaundry.ev
to test the general functionality of the model.

** hospital-test1.bat **
This batch files test the atomic hospital model using the hospitalMA-test1.ma
and no input file.  This tests the functionality of the normal distribution to ensure
that all the clean laundry is being turned into dirty laundry correctly.

** hospital-test2.bat **
This batch files tests the atomic hospital model using the hospitalMA-test2.ma
and no input file.  This tests that the model initializes correctly and responds to inputs.

** hospital-test3.bat **
This batch files tests the atomic hospital model using the hospitalMA-test3.ma
and hospital-test3.ev input file. This tests how the distribution of dirty laundry
generation behaves and ensures that very large numbers or time lines are handled correctly.

** laundromat-test1.bat **
This batch file tests the coupled laundromat model.  It uses laundromatMA-test1.ma
and laundromat-test1.ev input file.  This tests the general functionality of the model.

** laundryCleaning-test1.bat **
This batch file tests the  atomic laundry cleaning model. It uses laundryCleaningMA-test1.ma
and laundryCleaning-test1.ev input file.  This tests the response of the cleaning model to various
dirty laundry inputs at various times.

** laundryCleaning-test2.bat **
This batch file tests the  atomic laundry cleaning model. It uses laundryCleaningMA-test2.ma
and no input file.  This tests the response of the cleaning model to the initial condition of
dirty laundry and no input.

** laundryCleaning-test3.bat **
This batch file tests the  atomic laundry cleaning model. It uses laundryCleaningMA-test3.ma
and no input file.  This tests the response of the cleaning model to the initial condition of
no laundry and no input.

** laundryShipping-test1.bat **
This batch file tests the atomic laundry shipping model.  It uses laundryShippingMA-test1.ma and 
no input file.  This tests that the scheduled shipping functions correctly and that the
shortAmount outputs are raised correctly.

** laundryShipping-test2.bat **
This batch file tests the atomic laundry shipping model.  It uses laundryShippingMA-test2.ma and 
laundryShipping-test2.ev input file.  This tests the effects of input on the scheduled delivery and 
shortAmount outputs.