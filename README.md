SPCPoint
========

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
