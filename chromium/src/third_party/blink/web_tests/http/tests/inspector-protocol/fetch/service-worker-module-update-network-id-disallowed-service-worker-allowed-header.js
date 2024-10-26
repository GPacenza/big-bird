(async function(/** @type {import('test_runner').TestRunner} */ testRunner) {
  const test = await testRunner.loadScript(
      'resources/service-workers/service-worker-test.js');
  await test(testRunner, {
    description: 'disallowed by Service-Worker-Allowed header',
    type: 'module',
    serviceWorkerAllowedHeader: '/foo',
    update: true
  });
})
