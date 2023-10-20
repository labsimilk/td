//
// Copyright Aliaksei Levin (levlam@telegram.org), Arseny Smirnov (arseny30@gmail.com) 2014-2023
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
#pragma once

#include "td/telegram/DialogBoostLinkInfo.h"
#include "td/telegram/DialogId.h"
#include "td/telegram/td_api.h"

#include "td/actor/actor.h"

#include "td/utils/common.h"
#include "td/utils/Promise.h"
#include "td/utils/Slice.h"

namespace td {

class Td;

class BoostManager final : public Actor {
 public:
  BoostManager(Td *td, ActorShared<> parent);

  void get_dialog_boost_status(DialogId dialog_id, Promise<td_api::object_ptr<td_api::chatBoostStatus>> &&promise);

  void boost_dialog(DialogId dialog_id, Promise<Unit> &&promise);

  Result<std::pair<string, bool>> get_dialog_boost_link(DialogId dialog_id);

  void get_dialog_boost_link_info(Slice url, Promise<DialogBoostLinkInfo> &&promise);

  td_api::object_ptr<td_api::chatBoostLinkInfo> get_chat_boost_link_info_object(const DialogBoostLinkInfo &info) const;

  void get_dialog_boosts(DialogId dialog_id, bool only_gift_codes, const string &offset, int32 limit,
                         Promise<td_api::object_ptr<td_api::foundChatBoosts>> &&promise);

 private:
  void tear_down() final;

  Td *td_;
  ActorShared<> parent_;
};

}  // namespace td