# SparkOS

     一个基于x86架构的操作系统，从零开始开发，准备长期维护，主要出于个人兴趣，不和任何现有的
     操作系统比较，但是肯定会借鉴现有操作系统的一些特性和视觉效果，准备通过开发这个操作系统，
     对计算机整体的运行机制能够逐渐加深理解，虽然工作从事的不是这方面的工作，
     但是也是做软件开发的，所以肯定会对工作中遇到的问题的理解有些不同的思路和理解的。

     目前这个操作系统已经是可以运行了，但是基于快速能有一个实际的效果可以看到的想法，
     目前实现的模块有引导模块，图形显示模块，键盘和鼠标的驱动模块，以及一个英文和数字的字库。

      **引导模块** ：由于目前开发的版本是基于x86架构的，而现如今除了pc外，
      大多数设备其实都是arm架构的，所以将来肯定会开发arm架构的版本。
      x86和arm架构主要还是引导这块的差异比较大，而arm由于是精简指令集，
      所以会比x86的开发略微简单一些。

     所以首个版本之所以先开发x86的版本，一个是由于x86经过这么多年，资料足够丰富，
     基本所有遇到的问题也比较容易找到解决方法,当然arm现在资料这方面也是足够丰富，
     总之这方面二者对开发者来说都还是比较友好的。 

     另外一个原因是，由于开发过程中主要还是使用模拟器来开发的，
     比如这个操作系统就是qemu上开发的,对于x86来说，由于这么多年下来，
     各种标准体系都是比较成熟的，所以如果在模拟器上能够跑通了，移植到真机上，
     基本也没什么问题。而arm设备由于真机上会存在各种的定制修改问题，
     所以不能保证在模拟器上实现后可以无缝的移植到真机上，
     所以这是我们考虑先开发一个x86版本的重要原因。

     最后就是x86主要是pc机在使用，我们后面硬件开发主要还是先准备用键盘和鼠标，
     而arm设备以触摸为主，所以这也是我们考虑先开发x86版本的原因。

     **图形显示** ：既然准备开一个操作系统，
     所以我们一开始就打算必须要有图形显示的效果，由于现有的一些操作系统的开发资料，
     大多还是基于命令行开发的，所以如果我们还是开发一个黑色背景的命令行，
     就会感觉没什么意思，所以我们开始就打算打开一个带图形界面的，
     当然目前这个版本也有命令行的模式，只不过由于以图形界面为主，
     目前需要通过修改代码的方式来在图形模式和命令行模式之间切换,
     将来会做成像现在操作系统那样通过图形界面点击一个按钮，打开一个命令行窗口这样。

     **键盘和鼠标的驱动** ：键盘和鼠标的开发主要是查找他们的标准驱动开发资料，
     根据开发手册，往指定的寄存器中写入或者读取属性，
     解析数据也是根据开发手册上的来做。驱动开发既有涉及到汇编的使用，也有c语言的使用，
    总的来说驱动开发是比较枯燥的，基本就是根据开发手册来实现。

     **字库** ：字库目前只支持英文和数字，汉字的话由于数量太多了，所以暂时先不考虑，
     后期再看。具体的字库是通过开发了一个java的程序来实现的，
     源码在这里：https://gitee.com/qichanna/MakeFont](https://github.com/qichanna/MakeFont

     目前来说就实现了以上部分，后面会继续开发的，但是由于个人时间不确定，
     所以说准备做长期开发的准备，甚至终身开发的准备，哈哈，
     目标就是最终可以向主流的操作系统靠拢。下面先放出这个初始的截图，虽然简陋，
     不过开发出来还是很有成就感的,可以看到我们主要现在还是模仿windows的，
     最下面有一个toolbar，左边有个按键，点击后会显示进一步的窗口，
     这些功能目前还都没完成，后面会陆续添加上。
     
![pic](https://github.com/qichanna/SparkOS/assets/6308765/c5cbc701-d41d-4d29-abee-474cad74d8d7)



     
