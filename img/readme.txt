1. 发布版本："SDF 1.0.35.24.0618-08:43"
2. 版本说明：
    （1）该版本已实现《安全芯片SDK规范说明》中所有规范的函数，各函数参考使用位于demo目录中。
    （2）该版本产生日志的方法：
        （2.1）libsdf_crypto.so：该版本为文件日志版本，在/data/local/tmp目录创建sdf.txt空文件，重新运行后即会在/data/local/tmp产生sdflog.txt日志文件。
        （2.2）libsdf_crypto_logcat.so：该版本为logcat日志版本，过滤标签为SafeKey, 如logcat -s SafeKey。
3. 链接方法：
    （3.1）-lsdf_crypto
    （3.2）-lsdf_crypto_logcat
