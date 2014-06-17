// Copyright (C) 2013 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// A wrapper object for Storage that stores data with a checksum and a
// timestamp. The existence of checksum and timestamp fields is transparent to
// the user of the object.

#ifndef I18N_ADDRESSINPUT_VALIDATING_STORAGE_H_
#define I18N_ADDRESSINPUT_VALIDATING_STORAGE_H_

#include <libaddressinput/storage.h>
#include <libaddressinput/util/basictypes.h>
#include <libaddressinput/util/scoped_ptr.h>

#include <string>

namespace i18n {
namespace addressinput {

// Wraps Storage to add checksum and timestamp to stored data. Sample usage:
//    scoped_ptr<Storage> file_storage = ...;
//    ValidatingStorage storage(file_storage));
//    storage.Put("key", new std::string("data"));
//    scoped_ptr<ValidatingStorage::Callback> data_ready(BuildCallback(
//        this, &MyClass::OnDataReady));
//    storage.Get("key", *data_ready);
class ValidatingStorage : public Storage {
 public:
  // Takes ownership of |storage|.
  explicit ValidatingStorage(Storage* storage);
  virtual ~ValidatingStorage();

  // Storage implementation.
  virtual void Put(const std::string& key, std::string* data);

  // Storage implementation.
  // If the data is invalid, then |data_ready| will be called with (false, key,
  // empty-string). If the data is valid, but stale, then |data_ready| will be
  // called with (false, key, stale-data). If the data is valid and fresh, then
  // |data_ready| will be called with (true, key, fresh-data).
  virtual void Get(const std::string& key, const Callback& data_ready) const;

 private:
  // The storage being wrapped.
  scoped_ptr<Storage> wrapped_storage_;

  DISALLOW_COPY_AND_ASSIGN(ValidatingStorage);
};

}  // namespace addressinput
}  // namespace i18n

#endif  // I18N_ADDRESSINPUT_VALIDATING_STORAGE_H_
