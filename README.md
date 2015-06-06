# PWM Analyzer for Saleae Logic

This plugin for [Saleae Logic][logic] allows you to analyze a PWM
stream as commonly found in RC.

![logic analyzer](https://github.com/dustin/logic-pwm/raw/master/docs/pwm-logic.png)

## Exporting

The analyzer exports to a simple csv format with a timestamp and the
value read at that timestamp.

```csv
Time [s],High,Low,Duty,Frequency
0.000000000000000,1497,20000,6.964123,46.5
0.042996833333333,1494,20000,6.954384,46.5
0.085988500000000,1501,20000,6.981431,46.5
0.107489583333333,1437,20000,6.706990,46.6
0.128927416666667,1506,20000,7.004859,46.5
0.150433916666667,1577,20000,7.309066,46.3
0.172011000000000,1574,20000,7.299042,46.4
0.193585750000000,1606,20000,7.437048,46.3
0.236799666666667,1656,20000,7.648974,46.2
0.258456166666667,1698,20000,7.828438,46.1
0.280154833333333,1677,20000,7.737729,46.1
```

## Building

Download the [Logic SDK][sdk] and extract it somewhere on your
machine.  In my case, it's `~/stuff/SaleaeAnalyzerSdk-1.1.32`.

Clone the repo and cd into the top level of it:

    git clone https://github.com/dustin/logic-pwm
    cd logic-pwm

Symlink the `include` and `lib` directories into your tree:

    ln -s ~/stuff/SaleaeAnalyzerSdk-1.1.32/{include,lib} .

Run the build script:

    ./build_analyzer.py

## Installing

In the Develoepr tab in Logic preferences, specify the path for
loading new plugins, then copy the built plugin into that location:

    cp release/* /path/specified/in/Logic/preferences

[logic]: https://www.saleae.com/downloads
[sdk]: http://support.saleae.com/hc/en-us/articles/201104644-Analyzer-SDK
