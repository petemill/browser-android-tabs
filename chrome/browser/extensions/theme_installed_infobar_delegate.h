// Copyright (c) 2011 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef CHROME_BROWSER_EXTENSIONS_THEME_INSTALLED_INFOBAR_DELEGATE_H_
#define CHROME_BROWSER_EXTENSIONS_THEME_INSTALLED_INFOBAR_DELEGATE_H_

#include <string>

#include "base/compiler_specific.h"
#include "components/infobars/core/confirm_infobar_delegate.h"
#include "content/public/browser/notification_observer.h"
#include "content/public/browser/notification_registrar.h"
#include "extensions/common/extension_id.h"

class InfoBarService;
class ThemeService;

namespace extensions {
class ExtensionService;
}

// When a user installs a theme, we display it immediately, but provide an
// infobar allowing them to cancel.
class ThemeInstalledInfoBarDelegate : public ConfirmInfoBarDelegate,
                                      public content::NotificationObserver {
 public:
  // Creates a theme installed infobar and delegate and adds the infobar to
  // |infobar_service|, replacing any previous theme infobar.
  static void Create(InfoBarService* infobar_service,
                     extensions::ExtensionService* extension_service,
                     ThemeService* theme_service,
                     const std::string& theme_name,
                     const std::string& theme_id,
                     const std::string& previous_theme_id,
                     bool previous_using_system_theme);

 private:
  ThemeInstalledInfoBarDelegate(extensions::ExtensionService* extension_service,
                                ThemeService* theme_service,
                                const std::string& theme_name,
                                const std::string& theme_id,
                                const std::string& previous_theme_id,
                                bool previous_using_system_theme);
  ~ThemeInstalledInfoBarDelegate() override;

  // ConfirmInfoBarDelegate:
  infobars::InfoBarDelegate::InfoBarIdentifier GetIdentifier() const override;
  const gfx::VectorIcon& GetVectorIcon() const override;
  ThemeInstalledInfoBarDelegate* AsThemePreviewInfobarDelegate() override;
  base::string16 GetMessageText() const override;
  int GetButtons() const override;
  base::string16 GetButtonLabel(InfoBarButton button) const override;
  bool Cancel() override;

  // content::NotificationObserver:
  void Observe(int type,
               const content::NotificationSource& source,
               const content::NotificationDetails& details) override;

  extensions::ExtensionService* extension_service_;
  ThemeService* theme_service_;

  // Name of theme that's just been installed.
  std::string theme_name_;

  // ID of theme that's just been installed.
  std::string theme_id_;

  // Used to undo theme install.
  std::string previous_theme_id_;
  bool previous_using_system_theme_;

  // Registers and unregisters us for notifications.
  content::NotificationRegistrar registrar_;
};

#endif  // CHROME_BROWSER_EXTENSIONS_THEME_INSTALLED_INFOBAR_DELEGATE_H_
