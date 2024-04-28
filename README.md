# QML QAbstractListModel Demo
I wanted to play with subclassing a `QAbstractListModel`, and implementing
the functions needed to make the list items editable, ie `setData()` and `flags()`.

This small example houses a model, `TestModel` which is a `QAbstractListModel`,
that contains `TestData`, a plain/non-QObject class. The model is owned and
exposed by a controller, `TestCtlr`. Creative names, I know.
