# Unreal Course Homework

#### hw1

* 编译UE4，参考官方资料&课件完成。其中安装SetupAndroid部分脚本报错，参考该链接 https://answers.unrealengine.com/questions/963972/why-is-setupandroidbat-failing-with-default-setup.html 在脚本前后加入以下语句可解决。

  ```bash
  setx PATH "%USERPATH:~1,-1%;%PLATFORMTOOLS%"
  ```

* 打包了基本的第三人称场景为安卓apk，录制视频，见release的HW1，链接https://github.com/jsjtxietian/UnRealLearningProject/releases/tag/HW1


#### hw2

* 完成了靶子，分三级计分，最外圈10分，中圈20分，内圈30分。
* 完成了射击相关的函数逻辑，按音量+可以发射出圆形的子弹，击中靶子相应区域可以得分，显示在HUD上
* 视频和apk见最新的release，HW2。