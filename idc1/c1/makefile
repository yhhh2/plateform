#框架头文件路径
PUBH=-I/project/public 
#框架cpp文件
PUBCPP=/project/public/_public.cpp


#all:crtsurfdata5 crtsurfdata2 crtsurfdata3 crtsurfdata4 crtsurfdata5 crtsurfdata
all:crtsurfdata

crtsurfdata1:crtsurfdata1.cc
		g++ -g -o crtsurfdata1 crtsurfdata1.cc $(PUBH) $(PUBCPP) -lm -lc
		cp crtsurfdata1 ../bin/.

crtsurfdata2:crtsurfdata2.cc
		g++ -g -o crtsurfdata2 crtsurfdata2.cc $(PUBH) $(PUBCPP) -lm -lc
		cp crtsurfdata2 ../bin/.
crtsurfdata3:crtsurfdata3.cc
		g++ -g -o crtsurfdata3 crtsurfdata3.cc $(PUBH) $(PUBCPP) -lm -lc
		cp crtsurfdata3 ../bin/.
crtsurfdata4:crtsurfdata4.cc
		g++ -g -o crtsurfdata4 crtsurfdata4.cc $(PUBH) $(PUBCPP) -lm -lc
		cp crtsurfdata4 ../bin/.
crtsurfdata5:crtsurfdata5.cc
		g++ -g -o crtsurfdata5 crtsurfdata5.cc $(PUBH) $(PUBCPP) -lm -lc
		cp crtsurfdata5 ../bin/.
crtsurfdata:crtsurfdata.cc
		g++ -g -o crtsurfdata crtsurfdata.cc $(PUBH) $(PUBCPP) -lm -lc
		cp crtsurfdata ../bin/.




clean:
	rm crtsurfdata1 crtsurfdata2 crtsurfdata3 crtsurfdata4 crtsurfdata5 crtsurfdata
