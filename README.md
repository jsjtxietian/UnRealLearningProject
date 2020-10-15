# Unreal Course Homework

#### hw1

* 编译UE4，参考官方资料&课件完成。其中安装SetupAndroid部分脚本报错，参考该链接 https://answers.unrealengine.com/questions/963972/why-is-setupandroidbat-failing-with-default-setup.html 在脚本前后加入以下语句可解决。

  ```bash
  setx PATH "%USERPATH:~1,-1%;%PLATFORMTOOLS%"
  ```

* 打包了基本的第三人称场景为安卓apk，录制视频，见release的HW1，链接https://github.com/jsjtxietian/UnRealLearningProject/releases/tag/HW1

