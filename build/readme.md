# Build Scripts

The scripts must have this directory as working directory.

`dep_*` files are dependencies of the scripts and should not be called directly.


### `*.sh` Scripts

They return __0__ on success and __1__ on error.
Eexcept the `pack_*` scripts don't.


## Build
```sh
./build.sh [cleanAll] cmake make
```


---

---

### files to edit on version update

- `build/dep_vstr.txt`
- _todo ..._
