// Copyright 2015 The Chromium Authors
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "net/http/http_auth_multi_round_parse.h"

#include <string_view>

#include "base/strings/string_util.h"
#include "net/http/http_auth.h"
#include "net/http/http_auth_challenge_tokenizer.h"
#include "net/http/http_auth_scheme.h"
#include "testing/gtest/include/gtest/gtest.h"

namespace net {

TEST(HttpAuthHandlerNegotiateParseTest, ParseFirstRoundChallenge) {
  // The first round should just consist of an unadorned header with the scheme
  // name.
  HttpAuthChallengeTokenizer challenge("Negotiate");
  EXPECT_EQ(
      HttpAuth::AUTHORIZATION_RESULT_ACCEPT,
      ParseFirstRoundChallenge(HttpAuth::AUTH_SCHEME_NEGOTIATE, &challenge));
}

TEST(HttpAuthHandlerNegotiateParseTest,
     ParseFirstNegotiateChallenge_UnexpectedToken) {
  // If the first round challenge has an additional authentication token, it
  // should be treated as an invalid challenge from the server.
  HttpAuthChallengeTokenizer challenge("Negotiate Zm9vYmFy");
  EXPECT_EQ(
      HttpAuth::AUTHORIZATION_RESULT_INVALID,
      ParseFirstRoundChallenge(HttpAuth::AUTH_SCHEME_NEGOTIATE, &challenge));
}

TEST(HttpAuthHandlerNegotiateParseTest,
     ParseFirstNegotiateChallenge_BadScheme) {
  HttpAuthChallengeTokenizer challenge("DummyScheme");
  EXPECT_EQ(
      HttpAuth::AUTHORIZATION_RESULT_INVALID,
      ParseFirstRoundChallenge(HttpAuth::AUTH_SCHEME_NEGOTIATE, &challenge));
}

TEST(HttpAuthHandlerNegotiateParseTest, ParseLaterRoundChallenge) {
  // Later rounds should always have a Base64 encoded token.
  HttpAuthChallengeTokenizer challenge("Negotiate Zm9vYmFy");
  std::string encoded_token;
  std::string decoded_token;
  EXPECT_EQ(
      HttpAuth::AUTHORIZATION_RESULT_ACCEPT,
      ParseLaterRoundChallenge(HttpAuth::AUTH_SCHEME_NEGOTIATE, &challenge,
                               &encoded_token, &decoded_token));
  EXPECT_EQ("Zm9vYmFy", encoded_token);
  EXPECT_EQ("foobar", decoded_token);
}

TEST(HttpAuthHandlerNegotiateParseTest,
     ParseAnotherNegotiateChallenge_MissingToken) {
  HttpAuthChallengeTokenizer challenge("Negotiate");
  std::string encoded_token;
  std::string decoded_token;
  EXPECT_EQ(
      HttpAuth::AUTHORIZATION_RESULT_REJECT,
      ParseLaterRoundChallenge(HttpAuth::AUTH_SCHEME_NEGOTIATE, &challenge,
                               &encoded_token, &decoded_token));
}

TEST(HttpAuthHandlerNegotiateParseTest,
     ParseAnotherNegotiateChallenge_InvalidToken) {
  HttpAuthChallengeTokenizer challenge("Negotiate ***");
  std::string encoded_token;
  std::string decoded_token;
  EXPECT_EQ(
      HttpAuth::AUTHORIZATION_RESULT_INVALID,
      ParseLaterRoundChallenge(HttpAuth::AUTH_SCHEME_NEGOTIATE, &challenge,
                               &encoded_token, &decoded_token));
}

// The parser assumes that all authentication scheme names are lowercase.
TEST(HttpAuthHandlerNegotiateParseTest, AllSchemesAreCanonical) {
  EXPECT_EQ(base::ToLowerASCII(kBasicAuthScheme), kBasicAuthScheme);
  EXPECT_EQ(base::ToLowerASCII(kDigestAuthScheme), kDigestAuthScheme);
  EXPECT_EQ(base::ToLowerASCII(kNtlmAuthScheme), kNtlmAuthScheme);
  EXPECT_EQ(base::ToLowerASCII(kNegotiateAuthScheme), kNegotiateAuthScheme);
  EXPECT_EQ(base::ToLowerASCII(kMockAuthScheme), kMockAuthScheme);
}

}  // namespace net
