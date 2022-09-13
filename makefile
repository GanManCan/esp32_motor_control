
all:
	make -f ./tests/makefiles/MakefileMotorMath.mk 
	make -f ./tests/makefiles/MakefilePidControl.mk
	make -f ./tests/makefiles/MakefileSvpwmGen.mk

clean:
	make -f ./tests/makefiles/MakefileMotorMath.mk clean
	make -f ./tests/makefiles/MakefilePidControl.mk clean
	make -f ./tests/makefiles/MakefileSvpwmGen.mk clean

motormathTest:
	make -f ./tests/makefiles/MakefileMotorMath.mk

pidControlTest:
	make -f ./tests/makefiles/MakefilePidControl.mk 

svpwmGenTest:
	make -f ./tests/makefiles/MakefileSvpwmGen.mk

