import importlib

error_checker = importlib.import_module("fedcm.support.request-params-check")


def main(request, response):
    request_error = error_checker.tokenCheck(request)
    if (request_error):
        return request_error

    response.headers.set(b"Content-Type", b"application/json")
    response.headers.set(b"Access-Control-Allow-Origin",
                         request.headers.get(b"Origin"))
    response.headers.set(b"Access-Control-Allow-Credentials", "true")

    account = request.POST.get(b"account_id").decode("utf-8")
    return "{\"continue_on\": \"resolve_with_ot_token.html?selected=%s\"}" % (
        account)
