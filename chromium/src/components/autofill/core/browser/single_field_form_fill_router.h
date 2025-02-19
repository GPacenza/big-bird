// Copyright 2021 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef COMPONENTS_AUTOFILL_CORE_BROWSER_SINGLE_FIELD_FORM_FILL_ROUTER_H_
#define COMPONENTS_AUTOFILL_CORE_BROWSER_SINGLE_FIELD_FORM_FILL_ROUTER_H_

#include <string>
#include <vector>

#include "base/memory/raw_ptr.h"
#include "base/memory/raw_ref.h"
#include "components/autofill/core/browser/ui/suggestion.h"
#include "components/autofill/core/common/form_data.h"

namespace autofill {

class AutocompleteHistoryManager;
class AutofillClient;
class AutofillField;
class FormStructure;
class IbanManager;
class MerchantPromoCodeManager;

// Owned by BrowserAutofillManager, and is one per frame. Routes single field
// form filling requests to direct them to Autocomplete, merchant promo codes or
// IBAN.
// TODO: crbug.com/374086145 - Make per-tab.
class SingleFieldFormFillRouter {
 public:
  // Some single-field form fillers return suggestions asynchronously. This
  // callback is used to eventually return suggestions. `field_id` identifies
  // the field the query refer to. `suggestions` is the list of fetched
  // suggestions.
  // TODO(crbug.com/374266445): This should be a `base::OnceCallback<>`. It is
  // currently a repeating callback, because the `SingleFieldFormFillRouter`
  // asks all available fillers using `OnGetSingleFieldSuggestions()`, until the
  // first one returns true. This requires passing the callback to all
  // fillers (even though only one of them will end up calling it).
  using OnSuggestionsReturnedCallback =
      base::RepeatingCallback<void(FieldGlobalId,
                                   const std::vector<Suggestion>&)>;

  explicit SingleFieldFormFillRouter(
      AutocompleteHistoryManager* autocomplete_history_manager,
      IbanManager* iban_manager,
      MerchantPromoCodeManager* merchant_promo_code_manager);
  SingleFieldFormFillRouter(const SingleFieldFormFillRouter&) = delete;
  SingleFieldFormFillRouter& operator=(const SingleFieldFormFillRouter&) =
      delete;
  virtual ~SingleFieldFormFillRouter();

  // Routes every field in a form to its correct single-field form filler,
  // calling OnWillSubmitFormWithFields() with the vector of fields for that
  // specific filler. If |form_structure| is not nullptr, then the fields in
  // |form| and |form_structure| should be 1:1. It is possible for
  // |form_structure| to be nullptr while |form| has data, which means there
  // were fields in the form that were not able to be parsed as autofill fields.
  virtual void OnWillSubmitForm(const FormData& form,
                                const FormStructure* form_structure,
                                bool is_autocomplete_enabled);

  // Gets suggestions for a given field. In the case of Autocomplete, this is
  // through a DB query, though it could be different for other fill types.
  // `client` is used for functionality such as checking if autocomplete is
  // enabled, or checking if the URL we navigated to is blocklisted for the
  // specific single field form filler that we are trying to retrieve
  // suggestions from. `field` is the given field.
  //
  // The boolean return value denotes whether a single-field form filler claims
  // the opportunity to fill this field. If the return value is `false`, the
  // `callback` is not called. If the return value is `true`, it may be called
  // synchronously or asynchronously or not at all (e.g., querying autocomplete
  // suggestions cancels pending queries).
  [[nodiscard]] virtual bool OnGetSingleFieldSuggestions(
      const FormStructure* form_structure,
      const FormFieldData& field,
      const AutofillField* autofill_field,
      const AutofillClient& client,
      OnSuggestionsReturnedCallback on_suggestions_returned);

  // Runs when a form is going to be submitted. In the case of Autocomplete, it
  // saves the given |fields| that are eligible to be saved as new or updated
  // Autocomplete entries, which can then be served in the future as
  // suggestions. This update is dependent on whether we are running in
  // incognito and if Autocomplete is enabled or not. |fields| can be empty.
  virtual void OnWillSubmitFormWithFields(
      const std::vector<FormFieldData>& fields,
      bool is_autocomplete_enabled);

  // Cancels all pending queries. This is only applicable to single-field
  // fillers that fetch suggestions asynchronously.
  virtual void CancelPendingQueries();

  // If applicable, removes the currently-selected suggestion from the database.
  // `type` is the SuggestionType of the suggestion to be
  // removed.
  virtual void OnRemoveCurrentSingleFieldSuggestion(
      const std::u16string& field_name,
      const std::u16string& value,
      SuggestionType type);

  // Invoked when the user selects `suggestion` in the list of suggestions. For
  // Autocomplete, this function logs the DaysSinceLastUse of the Autocomplete
  // entry associated with the value of the suggestion.
  virtual void OnSingleFieldSuggestionSelected(const Suggestion& suggestion);

 private:
  // Handles autocompleting single fields. The `AutocompleteHistoryManager` is
  // a KeyedService that outlives the `SingleFieldFormFillRouter`.
  // TODO(crbug.com/40941458): Once WebView doesn't have an
  // AutocompleteHistoryManager anymore, this should become a raw_ptr instead.
  raw_ref<AutocompleteHistoryManager> autocomplete_history_manager_;

  // Handles autofilling IBAN fields. Can be null on unsupported platforms, but
  // otherwise outlives the `SingleFieldFormFillRouter`, since it is a
  // KeyedService.
  raw_ptr<IbanManager> iban_manager_;

  // Handles autofilling merchant promo code fields. Can be null on unsupported
  // platforms, but otherwise outlives the `SingleFieldFormFillRouter`, since it
  // is a KeyedService.
  raw_ptr<MerchantPromoCodeManager> merchant_promo_code_manager_;
};

}  // namespace autofill

#endif  // COMPONENTS_AUTOFILL_CORE_BROWSER_SINGLE_FIELD_FORM_FILL_ROUTER_H_
