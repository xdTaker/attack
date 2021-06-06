## build
全编译安装
``` bash
sh test-make.sh
```
编译安装cap模块
``` bash
sh cap-make.sh
```
编译安装proto模块
``` bash
sh proto-make.sh
```
编译安装base模块
``` bash
sh base-make.sh
```
安装工具
``` bash
sh tool/tool-make.sh # 工具将安装在系统目录
```

## 目录结构
|--libs 库  
|　　|--base 公共基础库  
|　　|--proto 网络库  
|　　|--pcap 数据包文件处理模块  
|　　|--attack 网络攻击模块  
|　　|--3rd-party 第三方库  
|--tool 工具集  
|--example 测试及调用样例  
|--data 数据  
|　　|--pkgs 数据包  
|--reference 参考资料  
|--temp 鸡肋文件  
