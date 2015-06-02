# PWM Analyzer for Saleae Logic

This plugin for [Saleae Logic][logic] allows you to analyze a PWM
stream as commonly found in RC.

![logic analyzer](https://github.com/dustin/logic-pwm/raw/master/docs/pwm-logic.png)

## Exporting

The analyzer exports to a simple csv format with a timestamp and the
value read at that timestamp.

```csv
Time [s],Value
0.014983000000000,1458
0.031408250000000,1475
0.047834250000000,1491
0.064262375000000,1506
0.080689000000000,1523
0.097115625000000,1539
0.113543000000000,1555
0.129969625000000,1571
0.146394750000000,1588
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
