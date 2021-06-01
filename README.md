SPCPoint
========
[![Travis Build Status](https://travis-ci.com/loveemu/spcpoint.svg?branch=master)](https://travis-ci.com/loveemu/spcpoint) [![AppVeyor Build Status](https://ci.appveyor.com/api/projects/status/19v8biaxryhcbl28/branch/master?svg=true)](https://ci.appveyor.com/project/loveemu/spcpoint/branch/master)

[SPCPoint](https://github.com/loveemu/spcpoint) is a simple command-line SPC tagger.

SPCPoint is heavily inspired by [PSFPoint](https://github.com/loveemu/psfpoint) written by Neill Corlett.

Usage
-----

`spcpoint [-tf] [-variable=value ...] spc-file(s)`

`-tf`
  : Sets the title tag according to the filename.
    Obvious track numbers, "%20", and other garbage is processed.

`-variable=value`
  : Sets the given variable name to the given value.   
    Note that if this has spaces in it, you have to enclose the option in quotation marks, i.e. `"-variable=value with spaces"`   
    If you want to delete a variable, just say: `-variable=`

`spc-file(s)`
  : One or more SPC filenames.  Wildcards are accepted.

### List of tags

|Tag                    |Description                                                                 |
|-----------------------|----------------------------------------------------------------------------|
|title=[string]         |Song name                                                                   |
|game=[string]          |Game name                                                                   |
|artist=[string]        |Artist's name                                                               |
|snsfby=[string]        |Dumper name                                                                 |
|year=[integer]         |Copyright year                                                              |
|comment=[string]       |Comments                                                                    |
|copyright=[string]     |Publisher's name                                                            |
|volume=[number]        |Amplification value to apply to output (1.0 = normal volume)                |
|length=[time]          |Song length excluding fadeouts (Note: it will delete all extended timings!) |
|fade=[time]            |Fade length                                                                 |
|created_at=[date]      |Date song was dumped                                                        |
|emulator=[id or name]  |Emulator used                                                               |
|soundtrack=[string]    |Official soundtrack title                                                   |
|disc=[integer]         |OST disc                                                                    |
|track=[integer(+char)] |OST track                                                                   |
|intro=[time]           |Introduction length                                                         |
|loop=[time]            |Loop length                                                                 |
|end=[time]             |End length                                                                  |
|mute=[integer]         |Muted channels (a bit is set for each channel that's muted)                 |
|loopcount=[integer]    |Number of times to loop the loop section of the song                        |

Examples
--------

To set the game name of every SPC file in the current directory:

```
spcpoint "-game=Final Fantasy 5" *.spc
```

Or to set the volumes to 1.0:

```
spcpoint -volume=1 *.spc
```

Or to delete all comments:

```
spcpoint -comment= *.spc
```

The possibilities are endless!

Thanks to
---------

- Neill Corlett, for PSFPoint.
- Alpha-II Productions, for SNESAmp as an user-friendly ID666 tagger.
